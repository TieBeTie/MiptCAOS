#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <ctype.h>
#include <limits.h>
#include <wait.h>

#define MAX_CONN_QUEUE 1024
#define MAX_EVENTS 1024
#define DEBUG 0

typedef struct conn_data_t conn_data_t;
int listen_fd;
int epoll_fd;
char HOME[PATH_MAX] = "";

int conns = 0;

struct conn_data_t {
    int32_t type;
    int32_t sock_fd;
    int32_t file_fd;
    int32_t child_process;
    char* bytes;
    size_t count;
    size_t capacity;
    bool done;
};

int get_return_status(const char* path, char* string_response_status) {
    if (access(path, F_OK) != -1) {
        if (access(path, R_OK) != -1) {
            strcpy(string_response_status, "OK");
            return 200;
        } else {
            strcpy(string_response_status, "Forbidden");
            return 403;
        }
    } else {
        strcpy(string_response_status, "Not Found");
        return 404;
    }
}

size_t get_file_size(const char* path) {
    struct stat stat_struct;
    lstat(path, &stat_struct);
    return stat_struct.st_size;
}

void execute_and_join_to_epoll(const char* path, struct conn_data_t* data) {

    int fds_pair[2];
    socketpair(AF_UNIX, SOCK_STREAM, 0, fds_pair);

    pid_t pid = fork();

    if (pid == 0) {
        close(fds_pair[0]);
        dup2(fds_pair[1], 1);
        close(fds_pair[1]);
        close(epoll_fd);
        close(listen_fd);
        close(data->sock_fd);
        execlp(path, path, NULL);
        perror("error with exec");
        _exit(0);
    } else {

        close(fds_pair[1]);
        struct conn_data_t* new_data = (struct conn_data_t*)malloc(sizeof(struct conn_data_t));
        memset(new_data, 0, sizeof(struct conn_data_t));
        new_data->file_fd = fds_pair[0];
        new_data->type = 2;
        new_data->count = 0;
        new_data->capacity = 0;
        new_data->child_process = pid;
        new_data->sock_fd = dup(data->sock_fd);
        new_data->done = false;
        int flags = fcntl(new_data->file_fd, F_GETFL);
        fcntl(new_data->file_fd, F_SETFL, flags | O_NONBLOCK);
        struct epoll_event event_ready_read;
        event_ready_read.events = EPOLLIN | EPOLLERR | EPOLLRDHUP;
        event_ready_read.data.ptr = new_data;
        epoll_ctl(epoll_fd, EPOLL_CTL_ADD, new_data->file_fd, &event_ready_read);
    }
}

void read_file_and_send(const char* path, int32_t sock_fd) {
    int32_t fd = open(path, O_RDONLY);
    char buff[4096];
    size_t cnt;
    while ((cnt = read(fd, buff, sizeof(buff))) > 0) {
        write(sock_fd, buff, cnt);
    }
}

int http_answer(struct conn_data_t* data) {
    char method[20];
    char end_path[PATH_MAX];
    char HTTP_version[100];
    sscanf(data->bytes, "%s %s %s", method, end_path, HTTP_version);
    char full_path[PATH_MAX] = "";
    stpcpy(full_path, HOME);
    strcat(full_path, end_path);
    char string_response_status[400] = "";
    int response_status = get_return_status(full_path, string_response_status);
    // first response line
    dprintf(data->sock_fd, "HTTP/1.1 %d %s\r\n", response_status, string_response_status);
    if (response_status == 200) {
        if (access(full_path, X_OK) == -1) {
            size_t file_size = get_file_size(full_path);
            dprintf(data->sock_fd, "Content-Length: %ld\r\n\r\n", file_size);
            read_file_and_send(full_path, data->sock_fd);
        } else {
            execute_and_join_to_epoll(full_path, data);
            return 1;
        }
    } else {
        dprintf(data->sock_fd, "Content-Length: %d\r\n\r\n", 0);
    }
    return 0;
}

void process_read(struct conn_data_t* data) {
    if (data->capacity == 0) {
        data->bytes = (char*)malloc(8096 * sizeof(char));
        data->bytes[0] = '\0';
        data->capacity = 8096;
    } else if (data->capacity - data->count <= 8096) {
        data->bytes = (char*)realloc(data->bytes, data->capacity * 2 * sizeof(char));
        data->capacity *= 2;
    }
    char buffer[8096];
    int count = read(data->sock_fd, buffer, sizeof(buffer) - 1);
    buffer[count] = '\0';
    strcat(data->bytes, buffer);
    data->count += count;
    if (data->count >= 2 && data->bytes[data->count - 2] == '\r' && data->bytes[data->count - 1] == '\n') {
        data->done = true;
        shutdown(data->sock_fd, SHUT_RD);
    }
}

void process_child(struct conn_data_t* data) {
    if (data->capacity == 0) {
        data->bytes = (char*)malloc(8096 * sizeof(char));
        data->bytes[0] = '\0';
        data->capacity = 8096;
    } else if (data->capacity - data->count <= 8096) {
        data->bytes = (char*)realloc(data->bytes, data->capacity * 2 * sizeof(char));
        data->capacity *= 2;
    }
    char buffer[8096];
    int count = read(data->file_fd, buffer, sizeof(buffer) - 1);
    if (count == 0) {
        data->done = true;
        shutdown(data->file_fd, SHUT_RDWR);
        close(data->file_fd);
        waitpid(data->child_process, NULL, 0);
        return;
    } else if (count > 0) {
        buffer[count] = '\0';
        strcat(data->bytes, buffer);
        data->count += count;
    }
}

void handle_server_event(struct epoll_event* evt) {
    const uint32_t mask = evt->events;
    struct conn_data_t* evt_data = evt->data.ptr;
    if ((mask & EPOLLIN) || (mask & EPOLLERR) || (mask & EPOLLRDHUP)) {
        if (evt_data->type == 0) {
            int32_t sock = accept(listen_fd, (struct sockaddr*)NULL, NULL);
            if (sock <= 0) {
                return;
            }
            struct conn_data_t* data = (struct conn_data_t*)malloc(sizeof(struct conn_data_t));
            memset(data, 0, sizeof(struct conn_data_t));
            data->sock_fd = sock;
            data->type = 1;
            data->done = false;
            int flags = fcntl(data->sock_fd, F_GETFL);
            fcntl(data->sock_fd, F_SETFL, flags | O_NONBLOCK);

            struct epoll_event event_ready_read;
            event_ready_read.events = EPOLLIN | EPOLLERR | EPOLLRDHUP;
            event_ready_read.data.ptr = data;

            epoll_ctl(epoll_fd, EPOLL_CTL_ADD, data->sock_fd, &event_ready_read);
            ++conns;

        } else if (evt_data->type == 1) {
            process_read(evt_data);
            if (evt_data->done) {
                int type = http_answer(evt_data);
                if (type == 0) {
                    --conns;

                    close(evt_data->sock_fd);
                    shutdown(evt_data->sock_fd, SHUT_WR);
                }
                epoll_ctl(epoll_fd, EPOLL_CTL_DEL, evt_data->sock_fd, NULL);
                free(evt_data->bytes);
            }
        } else if (evt_data->type == 2) {
            process_child(evt_data);
            if (evt_data->done) {
                //dprintf(evt_data->sock_fd, "Content-Length: %ld\r\n\r\n", evt_data->count);
                write(evt_data->sock_fd, evt_data->bytes, evt_data->count);
                epoll_ctl(epoll_fd, EPOLL_CTL_DEL, evt_data->file_fd, NULL);
                shutdown(evt_data->sock_fd, SHUT_RDWR);
                close(evt_data->sock_fd);
                free(evt_data->bytes);
            }
        }
    }
}

sig_atomic_t stop = 0;

void stop_handler(int32_t sig_num) {
    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, listen_fd, NULL);
    close(epoll_fd);
    stop = 1;
    _exit(0);
}

int main(int argc, char** argv) {

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGPIPE);
    sigprocmask(SIG_BLOCK, &mask, NULL);

    if (DEBUG) {
        printf("%d\n", getpid());
    }

    stpcpy(HOME, argv[2]);
    strcat(HOME, "/");
    struct sigaction sigterm_act;
    memset(&sigterm_act, 0, sizeof(struct sigaction));
    sigterm_act.sa_handler = stop_handler;
    sigterm_act.sa_flags = SA_RESTART;
    sigaction(SIGTERM, &sigterm_act, NULL);
    sigaction(SIGINT, &sigterm_act, NULL);

    struct sockaddr_in server_address;

    listen_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(atoi(argv[1]));

    if (bind(listen_fd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("bind failed");
        exit(1);
    }

    listen(listen_fd, MAX_CONN_QUEUE);

    epoll_fd = epoll_create1(0);

    struct epoll_event event_ready_conn;
    struct conn_data_t* serv = malloc(sizeof(struct conn_data_t));
    memset(serv, 0, sizeof(struct conn_data_t));
    serv->type = 0;
    serv->file_fd = listen_fd;
    event_ready_conn.events = EPOLLIN | EPOLLERR | EPOLLRDHUP;
    event_ready_conn.data.ptr = serv;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd, &event_ready_conn);

    struct epoll_event pending[MAX_EVENTS];

    while (true) {

        int n = epoll_wait(epoll_fd, pending, MAX_EVENTS, -1);

        for (size_t i = 0; i < n; ++i) {
            handle_server_event(&pending[i]);
        }

        if (conns <= 0 && stop) {
            exit(0);
        }

    }

    return 0;

}

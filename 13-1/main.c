#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <ctype.h>

#define MAX_CONN 1024
#define MAX_CONN_QUEUE 1024
#define MAX_EVENTS 1024
#define DEBUG 0

int listen_fd;
int epoll_fd;

typedef struct {
    int type;
    int sock_fd;
    char* bytes;
    size_t count;
    bool done;
} conn_data_t;

void process_read(conn_data_t* data) {
    char buff[4096];
    size_t count = read(data->sock_fd, buff, sizeof(buff));
    for (size_t i = 0; i < count; ++i) {
        buff[i] = (char)toupper(buff[i]);
    }
    write(data->sock_fd, buff, count);
}

void handle_server_event(struct epoll_event* evt) {
    const uint32_t mask = evt->events;
    conn_data_t* evt_data = evt->data.ptr;
    if (mask & EPOLLIN) {
        if (evt_data->type == 0) {

            conn_data_t* data = (conn_data_t*)calloc(0, sizeof(*data));
            data->sock_fd = accept(listen_fd, (struct sockaddr*)NULL, NULL);
            data->type = 1;
            int flags = fcntl(data->sock_fd, F_GETFL);
            fcntl(data->sock_fd, F_SETFL, flags | O_NONBLOCK);

            struct epoll_event* event_ready_read = calloc(0, sizeof(*event_ready_read));
            event_ready_read->events = EPOLLIN;
            event_ready_read->data.ptr = data;

            epoll_ctl(epoll_fd, EPOLL_CTL_ADD, data->sock_fd, event_ready_read);
        } else {
            conn_data_t* data = evt->data.ptr;
            process_read(data);
        }
    }
}

void sigterm_handler(int signum) {
    _exit(0);
}

int main(int argc, char** argv) {

    if (DEBUG) {
        printf("%d\n", getpid());
    }
    struct sigaction sigterm_act;
    memset(&sigterm_act, 0, sizeof(struct sigaction));
    sigterm_act.sa_handler = sigterm_handler;
    sigterm_act.sa_flags = SA_RESTART;
    sigaction(SIGTERM, &sigterm_act, NULL);

    struct sockaddr_in server_address;

    listen_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(atoi(argv[1]));

    bind(listen_fd, (struct sockaddr*)&server_address, sizeof(server_address));

    listen(listen_fd, MAX_CONN_QUEUE);

    epoll_fd = epoll_create1(0);

    struct epoll_event event_ready_conn;
    conn_data_t* serv = calloc(0, sizeof(*serv));
    serv->type = 0;

    event_ready_conn.events = EPOLLIN;
    event_ready_conn.data.ptr = serv;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd, &event_ready_conn);

    struct epoll_event pending[MAX_EVENTS];

    while (true) {

        int n = epoll_wait(epoll_fd, pending, MAX_EVENTS, -1);

        for (size_t i = 0; i < n; ++i) {
            handle_server_event(&pending[i]);
        }

    }

    return 0;
}

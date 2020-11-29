#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

const uint64_t BUFF_SIZE = 4096;

void handle_read(uint64_t n,uint64_t* errors_count, uint64_t* warnings_count, char* buff, char* delim) {
    char* now_pos;
    while (now_pos = strtok(buff, delim)) {
      //  printf("%s\n", now_pos);
        char* first = strtok(now_pos, ":");
        char* second = strtok(now_pos, ":");
        printf("%s\n", first);
        printf("%s\n", second);
    }
}

int main(int argc, char** args) {

    char* file = args[1];

    int in = open(file, O_RDONLY);
    dup2(in, 0);
    close(in);

    int fds_pair[2];
    pipe(fds_pair);
    pid_t pid = fork();

    if (pid == 0) {
        close(fds_pair[0]);
        dup2(fds_pair[1], 1);
        close(fds_pair[1]);
        execlp("gcc", "gcc", "-o", "test", file, NULL);
    } else {
        close(fds_pair[1]);
        uint64_t count = 0;
        uint64_t now_count;
        char buff[BUFF_SIZE];
        uint64_t errors_count = 0;
        uint64_t warnings_count = 0;

        while ((now_count = read(fds_pair[0], buff, sizeof(buff))) > 0) {
            handle_read(now_count, buff)
        }
        wait(NULL);

    }

    return 0;
}

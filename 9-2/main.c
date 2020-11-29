#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

const int BUFF_SIZE = 5096;

int main() {

    int begin = fork();
    if (begin == 0) {
        int pid;
        int status;
        do {
            pid = fork();
            if (pid == -1) {
                perror("");
                exit(1);
            }
            if (pid == 0) {
                char buff[BUFF_SIZE];
                if (scanf("%s\n", buff) == EOF) {
                    exit(-1);
                }
            } else {
                waitpid(pid, &status, 0);
                exit((status >> 8) + 1);
            }
        } while(pid == 0);
        exit((status >> 8));
    } else {
        int status;
        waitpid(begin, &status, 0);
        printf("%d\n", (status >> 8));
    }

    return 0;
}

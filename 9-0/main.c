#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void print(int n, int count) {
    if (n == count) {
        printf("%d\n", n);
    } else {
        printf("%d ", n);
    }
}

int main(int argc, char** argv) {

    int n = atoi(argv[1]);
    int prevpid = -1;
    for (int i = 0; i < n; ++i) {
        int pid = fork();
        if (pid == 0) {
            if (prevpid != -1) {
              int status;
              waitpid(prevpid, &status,  0);
            }

            print(i + 1, n);
            fflush(stdout);
            break;
        } else {
            prevpid = pid;
        }
        int status;
        waitpid(prevpid, &status,  WSTOPPED);
    }

    int status;
    waitpid(prevpid, &status, 0);

    return 0;
}

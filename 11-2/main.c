#include <stdio.h>
#include <signal.h>
#include <sys/signalfd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define READ_BUFF_SIZE 4096
#define DEBUG_FLAG 0

void close_fds(FILE** fds, int n) {
    for (int i = 0; i < n; ++i) {
        fclose(fds[i]);
    }
}

int main(int argc, char** argv) {

    if (DEBUG_FLAG) {
        printf("%d\n", getpid());
    }

    FILE* fds[argc - 1];
    for (int i = 0; i < argc; ++i) {      //open files
        fds[i] = fdopen(open(argv[i + 1], O_RDONLY), "r");
    }

    sigset_t block;
    sigset_t catch;

    sigfillset(&block);

    sigemptyset(&catch);

    for (int i = 0; i < argc; ++i) {      // fill set
        sigaddset(&catch, SIGRTMIN + i);
    }

    if (sigprocmask(SIG_BLOCK, &block, NULL) == -1) {
        close_fds(fds, argc - 1);
        perror("can't block signals.");
        exit(1);
    }

    int signal_fd = signalfd(-1, &catch, 0);  // signal file descriptor
    struct signalfd_siginfo fdsi;         // struct with signal data.

    char must_exit = 0;
    while (!must_exit) {
        if (sizeof(fdsi) != read(signal_fd, &fdsi, sizeof(fdsi))) {
            close_fds(fds, argc - 1);
            perror("bad signal");
            exit(1);
        }
        if (fdsi.ssi_signo == SIGRTMIN) {
            must_exit = 1;
        } else {
            char buff[READ_BUFF_SIZE];
            memset(buff, 0, sizeof(buff));

            char* res = fgets(buff, sizeof(buff), fds[fdsi.ssi_signo - SIGRTMIN - 1]);

            if (res != NULL) {
                fputs(buff, stdout);
                fflush(stdout);
            }

        }
    }

    close_fds(fds, argc - 1);

    return 0;
}

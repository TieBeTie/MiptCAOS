#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/time.h>
#include <signal.h>
#include <stdio.h>

void set_time_limit(double sec) {
    struct itimerval itv;
    getitimer(ITIMER_PROF, &itv);
    itv.it_interval.tv_sec = 0;
    itv.it_interval.tv_usec = 0;
    itv.it_value.tv_sec = 0;
    itv.it_value.tv_usec = ((int) (sec * 10E6));
    setitimer(ITIMER_PROF, &itv, NULL);
}

void swap(volatile void* first, volatile void* second, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        *((unsigned char*)first + i) ^= *((unsigned char*)second + i);
        *((unsigned char*)second + i) ^= *((unsigned char*)first + i);
        *((unsigned char*)first + i) ^= *((unsigned char*)second + i);
    }
}

int main(int argc, char** argv) {

    int other_pair[2];
    int now_pair[2];

    pipe(other_pair);
    pipe(now_pair);

    fcntl(now_pair[0], F_SETFL, O_NONBLOCK);

    fcntl(other_pair[0], F_SETFL, O_NONBLOCK);

    char helper[4096];

    for (int i = 1; i < argc; ++i) {
        pid_t pid = fork();
        if (pid == 0) {
            close(now_pair[0]);
            if (i < argc - 1) {
                dup2(now_pair[1], 1);
            }
            close(now_pair[1]);
            close(other_pair[1]);
            if (i > 1) {
                dup2(other_pair[0], 0);
            }
            close(other_pair[0]);
            fclose(stderr);
            execlp(argv[i], argv[i], NULL);

            perror("");
            exit(1);
        } else {
            if (i == argc - 1) {
                close(now_pair[0]);
            }
            int status;
            waitpid(pid, &status, 0);
            if (i > 1 && i < argc - 1) {
                while (read(other_pair[0], helper, sizeof(helper)) > 0) {}
            }
        }
        swap(other_pair, now_pair, sizeof(int) * 2);
    }

    return 0;

}

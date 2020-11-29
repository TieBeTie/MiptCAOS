#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/time.h>
#include <signal.h>


void set_time_limit(double sec) {
    struct itimerval itv;
    getitimer(ITIMER_PROF, &itv);
    itv.it_interval.tv_sec = 0;
    itv.it_interval.tv_usec = 0;
    itv.it_value.tv_sec = 0;
    itv.it_value.tv_usec = ((int) (sec * 10E6));
    setitimer(ITIMER_PROF, &itv, NULL);
}

int main(int argc, char** argv) {

    char* first_cmd = argv[1];
    char* second_cmd = argv[2];

    int fds_pair[2];
    pipe(fds_pair);

    pid_t pid1 = fork();
    if (pid1 == 0) {
        close(fds_pair[0]);
        dup2(fds_pair[1], 1);
        close(fds_pair[1]);
        set_time_limit(0.4);
        execlp(first_cmd, first_cmd, NULL);
    } else {
        close(fds_pair[1]);
        pid_t pid2 = fork();
        if (pid2 == 0) {
            dup2(fds_pair[0], 0);
            close(fds_pair[0]);
            set_time_limit(0.4);
            execlp(second_cmd, second_cmd, NULL);
        } else {
            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);
        }
    }

    return 0;

}

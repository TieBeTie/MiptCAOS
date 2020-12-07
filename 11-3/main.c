#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

#define DEBUG_FLAG 0

volatile sig_atomic_t must_exit = 0;
int pid = 0;

void sigrtmin_handler(int signum, siginfo_t* info, void* ucontext) {
    if (info->si_value.sival_int == 0) {
        must_exit = 1;
        if (DEBUG_FLAG && pid == 0) {
            union sigval val;
            val.sival_int = 0;
            sigqueue(info->si_pid, signum, val);
        }
        return;
    }
    if (DEBUG_FLAG && pid != 0) {
        printf("Signal with int %d\n", info->si_value.sival_int);
        fflush(stdout);
    }
    union sigval val;
    val.sival_int = info->si_value.sival_int - 1;
    sigqueue(info->si_pid, signum, val);
}

int main() {

    if (DEBUG_FLAG) {
        pid = fork();
        printf("%d\n", pid);
    }

    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_sigaction = sigrtmin_handler;
    action.sa_flags = SA_RESTART | SA_SIGINFO;
    sigaction(SIGRTMIN, &action, NULL);

    sigset_t block;
    sigfillset(&block);
    sigdelset(&block, SIGRTMIN);
    sigprocmask(SIG_BLOCK, &block, NULL);

    if (pid != 0) {
        sleep(1);
        union sigval val;
        val.sival_int = 10;
        sigqueue(pid, SIGRTMIN, val);
    }

    while (!must_exit) {
        pause();
    }

    if (pid != 0) {
        wait(NULL);
    }

    return 0;

}

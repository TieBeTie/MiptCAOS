#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

volatile sig_atomic_t value;
volatile sig_atomic_t must_exit = 0;

void sigusr1_handler(int signum) {
    ++value;
}

void sigusr2_handler(int signum) {
    value *= -1;
}

void sigterm_handler(int signum) {
    must_exit = 1;
}

void signal_watch(
    struct sigaction* action,
    void(*handler)(int),
    int signum
) {
    memset(action, 0, sizeof(struct sigaction));
    action->sa_handler = handler;
    action->sa_flags = SA_RESTART;
    sigaction(signum, action, NULL);
}

int main() {

    struct sigaction sigterm_act;
    signal_watch(&sigterm_act, sigterm_handler, SIGTERM);
    struct sigaction sigusr1_act;
    struct sigaction sigusr2_act;
    signal_watch(&sigusr1_act, sigusr1_handler, SIGUSR1);
    signal_watch(&sigusr2_act, sigusr2_handler, SIGUSR2);

    setbuf(stdout, NULL);
    printf("%d\n", getpid());

    scanf("%d", &value);

    while (!must_exit) {
        pause();
        if (!must_exit) {
            printf("%d\n", value);
        }
    }

    return 0;
    
}

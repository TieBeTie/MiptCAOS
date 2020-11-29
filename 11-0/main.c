#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

volatile sig_atomic_t counter = 0;
volatile sig_atomic_t must_exit = 0;

void sigint_handler(int signum) {
    ++counter;
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

    struct sigaction sigint_act;
    struct sigaction sigterm_act;
    signal_watch(&sigint_act, sigint_handler, SIGINT);
    signal_watch(&sigterm_act, sigterm_handler, SIGTERM);

    setbuf(stdout, NULL);
    printf("%d\n", getpid());

    while (!must_exit) {
        pause();
    }

    printf("%d\n", counter);

    return 0;
}

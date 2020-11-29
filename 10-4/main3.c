
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int main(int argc, char* argv[]) {
    int pipes[2][2];
    pipe(pipes[0]);
    fcntl(pipes[0][0], F_SETFL, O_NONBLOCK); // to not wait

    pipe(pipes[1]);
    fcntl(pipes[1][0], F_SETFL, O_NONBLOCK);

    int pipe_num = 0;
    for (int i = 1; i < argc; ++i) {
        pid_t pid = fork();
        if (pid == 0) {
            close(pipes[pipe_num][0]);
            if (i < argc - 1) {                 // for the last we should just write using stdout
                dup2(pipes[pipe_num][1], 1);
            }
            close(pipes[pipe_num][1]);
            close(pipes[1 - pipe_num][1]);
            if (i > 1) {                        // for the first we should just read using stdin
                dup2(pipes[1 - pipe_num][0], 0);
            }
            close(pipes[1 - pipe_num][0]);
            execlp(argv[i], argv[i], NULL);
        } else {
            waitpid(pid, 0, 0);
        }
        pipe_num = 1 - pipe_num;
    }
}
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/time.h>
#include <signal.h>

int main(int argc, char** argv) {

    char* first_cmd = argv[1];
    char* second_cmd = argv[2];

    int fds_pair_first[2];
    pipe(fds_pair_first);

    int fds_pair_second[2];
    pipe(fds_pair_second);

    int now = 0;

    for (int i = 1; i < argc; ++i) {
      pid_t pid = fork();
      if (pid == 0) {
          if (i == 1) {
              close(fds_pair_first[1]);
              close((now == 0 ? fds_pair_first[0] : fds_pair_second[0]));
              close((now == 1 ? fds_pair_first[1] : fds_pair_second[1]));
              dup2(fds_pair_first[1], 1);
          } else if (i == argc - 1) {
              dup2((now == 1 ? fds_pair_first[0] : fds_pair_second[0]), 0);
          } else {
              close((now == 0 ? fds_pair_first[1] : fds_pair_second[1]));
              dup2((now == 0 ? fds_pair_first[1] : fds_pair_second[1]), 1);
              close((now == 0 ? fds_pair_first[0] : fds_pair_second[0]));
              close((now == 1 ? fds_pair_first[1] : fds_pair_second[1]));
              dup2((now == 1 ? fds_pair_first[0] : fds_pair_second[0]), 0);
          }
          execlp(argv[i], argv[i], NULL);
      } else {
          waitpid(pid, NULL, 0);
      }
      now = 1 - now;
    }


    return 0;

}

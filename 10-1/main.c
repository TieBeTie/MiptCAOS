#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

const uint64_t BUFF_SIZE = 4096;
const uint64_t FULL_BUFF_INITIAL_SIZE = 32000;

uint64_t get_num(char** buff) {
    uint64_t num = 0;
    while(**buff != '\0' && **buff - 48 >= 0 && **buff - 48 <= 9) {
        num *= 10;
        num +=  **buff - 48;
        ++*buff;
    }
    return num;
}

void handle_read(uint64_t* errors_count, uint64_t* warnings_count, char* buff, char* delim) {
    char* now_pos = buff;
    char tmp[100];
    int64_t now_error_line = -1;
    int64_t now_warning_line = -1;
    int64_t delim_len = strlen(delim);
    char* end = buff + strlen(buff);
    while ((end - now_pos > 0) && (now_pos = strstr(now_pos, delim))) {
      now_pos += delim_len + 1;
      int64_t line = get_num(&now_pos);
      ++now_pos;
      get_num(&now_pos);
      ++now_pos;
      sscanf(now_pos, "%s", tmp);
      if (strcmp(tmp, "error:") == 0 && line != now_error_line) {
          now_error_line = line;
          ++*errors_count;
      } else if (strcmp(tmp, "warning:") == 0 && line != now_warning_line) {
          now_warning_line = line;
          ++*warnings_count;
      }
    }
}

int main(int argc, char** args) {

    char* file = args[1];

    int in = open(file, O_RDONLY);
    dup2(in, 0);
    close(in);

    int fds_pair[2];
    pipe(fds_pair);
    pid_t pid = fork();

    if (pid == 0) {
        close(fds_pair[0]);
        dup2(fds_pair[1], 2);
        close(fds_pair[1]);
        execlp("gcc", "gcc", "-o", "test", file, NULL);
    } else {
        close(fds_pair[1]);
        uint64_t now_count;

        char buff[BUFF_SIZE + 1];  // 1 extra byte for endstr
        memset(buff, '\0', sizeof(buff));

        uint64_t buff2_size = FULL_BUFF_INITIAL_SIZE * sizeof(char);
        char* buff2 = (char*)malloc(buff2_size);

        memset(buff2, '\0', FULL_BUFF_INITIAL_SIZE * sizeof(char));
        uint64_t count = 0;
        uint64_t errors_count = 0;
        uint64_t warnings_count = 0;

        while ((now_count = read(fds_pair[0], buff, sizeof(buff) - 1)) > 0) {
            if (count == buff2_size - 1) {
                char* tmp = realloc(buff2, buff2_size * 2);
                if (tmp == NULL) {
                    free(buff2);
                    exit(1);
                } else {
                    buff2 = tmp;
                    buff2_size *= 2;
                }
            }
            buff[now_count] = '\0';
            strcat(buff2, buff);
            count += now_count;
        }

        wait(NULL);

        handle_read(&errors_count, &warnings_count, buff2, file);

        printf("%ld %ld\n", errors_count, warnings_count);
    }

    return 0;
}

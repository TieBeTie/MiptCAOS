#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char** argv) {

    int input = open(argv[1], O_RDONLY);

    if (input == -1) {
        return 0;
    }

    int value = 0;
    int next_pointer = 0;

    char space = ' ';

    do {
      int read_result_v = read(input, &value, sizeof(value));
      int read_pointer_p = read(input, &next_pointer, sizeof(next_pointer));

      if (read_result_v <= 0) {
          return 0;
      }

      printf("%d ", value);

      if (read_pointer_p <= 0) {
          return 0;
      }

      if (next_pointer != 0) {
        lseek(input, next_pointer, SEEK_SET);
      }

    } while (next_pointer != 0);

    close(input);

    return 0;

}

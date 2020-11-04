#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

const int OPEN_ERROR_CODE = -1;
const int INPUT_UNDEFINED_EXIT_CODE = 1;
const int OUTPUT_UNDEFINED_EXIT_CODE = 2;
const int OUTPUT_ERROR_EXIT_CODE = 3;

void final(int input_file, int numbers_file, int no_numbers_file) {
    close(input_file);
    close(numbers_file);
    close(no_numbers_file);
}

int main(int argc, char** argv) {

    int input_file = open(argv[1], O_RDONLY);
    if (input_file == -1) {
        return INPUT_UNDEFINED_EXIT_CODE;
    }

    int numbers_file = open(argv[2], O_WRONLY | O_CREAT, 0640);
    int no_numbers_file = open(argv[3], O_WRONLY | O_CREAT, 0640);
    if (numbers_file == OPEN_ERROR_CODE || no_numbers_file == OPEN_ERROR_CODE) {
        final(input_file, numbers_file, no_numbers_file);
        return OUTPUT_UNDEFINED_EXIT_CODE;
    }


    char ch;
    int read_result;
    do {
        read_result = read(input_file, &ch, 1);
        int write_result;
        if (read_result == -1) {
            final(input_file, numbers_file, no_numbers_file);
            return OUTPUT_ERROR_EXIT_CODE;
        }
        if (read_result > 0) {
            if (ch >= '0' && ch <= '9') {
                write_result = write(numbers_file, &ch, 1);
            } else {
                write_result = write(no_numbers_file, &ch, 1);
            }
            if (write_result == -1) {
                final(input_file, numbers_file, no_numbers_file);
                return OUTPUT_ERROR_EXIT_CODE;
            }
        }
    } while (read_result > 0);

    final(input_file, numbers_file, no_numbers_file);

    return 0;

}


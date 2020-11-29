#include <sys/mman.h> // mmap
#include <sys/stat.h> // fstat
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // atoi
#include <fcntl.h> // open
#include <unistd.h> // close
#include <stdint.h>

void save_to_i_j(char* data, int i, int j, size_t n, size_t w, size_t x, char* num_buf) {
    size_t pos = (n * w + 1) * i + j * w;
    sprintf(num_buf, "%ld", x);
    size_t len = strlen(num_buf);
    if (len < w) {
       for (size_t i = 0; i < w - len; ++i) {
          *(data + pos) = ' ';
          ++pos;
       }
    }
    for (size_t i = 0; i < len; ++i) {
       *(data + pos) = num_buf[i];
       ++pos;
    }
}

int main (int argc, char **argv) {
    char* file = argv[1];
    size_t n = atoi(argv[2]);
    size_t w = atoi(argv[3]);
    int fd = open(file, O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IROTH);
    lseek(fd,  n * n * w + n, SEEK_SET);
    write(fd, " ", 1);
    char* file_data = mmap(NULL, n * n * w + n, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (file_data == MAP_FAILED) {
        close(fd);
        return 0;
    }

    int left_corner = 0;
    int right_corner = n - 1;

    int top_corner = 0;
    int bottom_corner = n - 1;

    size_t x = 1;

    size_t max_x = n * n;

    char num_buf[w + 1];

    do {
        for (int i = left_corner; i <= right_corner && x <= max_x; ++i) {
            save_to_i_j(file_data, top_corner, i, n, w, x, num_buf);
            ++x;
        }
        ++top_corner;
        for (int i = top_corner; i <= bottom_corner && x <= max_x; ++i) {
            save_to_i_j(file_data, i, right_corner, n, w, x, num_buf);
            ++x;
        }
        --right_corner;
        for (int i = right_corner; i >= left_corner && x <= max_x; --i) {
            save_to_i_j(file_data, bottom_corner, i, n, w, x, num_buf);
            ++x;
        }
        --bottom_corner;
        for (int i = bottom_corner; i >= top_corner && x <= max_x; --i) {
            save_to_i_j(file_data, i, left_corner, n, w, x, num_buf);
            ++x;
        }
        ++left_corner;
    } while (x <= max_x);

    for (size_t i = 0; i < n; ++i) {
        size_t pos = (n * w + 1) * i + n * w;
        *(file_data + pos) = '\n';
    }

    msync(file_data, n * n * w + n, MS_SYNC);
    munmap(file_data, n * n * w + n);
    close(fd);

    return 0;
}

#include <stdio.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdint.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main (int argc, char** argv) {

    struct stat info;
    char *file = argv[1];
    int fd = open(file, O_RDONLY);
    lstat(file, &info);
    if (info.st_size == 0) {
        close(fd);
        return 0;
    }

    void* file_data = mmap(NULL, info.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    int value = *((int*) file_data);
    uint32_t next_position = *((uint32_t*) (file_data + sizeof(value)));
    printf("%d ", value);
    while (next_position != 0) {
        value = *((int*) (file_data + next_position));
        next_position = *((uint32_t*) (file_data + next_position + sizeof(value)));
        printf("%d ", value);
    }
    munmap(file_data, info.st_size);
    close(fd);

    return 0;
}

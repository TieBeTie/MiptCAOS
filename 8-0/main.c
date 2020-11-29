#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main (int argc, char** argv) {
    struct stat info;
    char *file = argv[1];
    int fd = open(file, O_RDONLY);
    lstat(file, &info);
    if (info.st_size == 0) {
        close(fd);
        return 0;
    }
    char* file_data = mmap(NULL, info.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    char* to_find = argv[2];
    char* position = file_data;
    while (position) {
        position = strstr(position, to_find);
        if (position) {
            printf("%ld\n", position - file_data);
            ++position;
        }
    }
    munmap(file_data, info.st_size);
    close(fd);
    return 0;
}

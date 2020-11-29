#include <stdio.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdint.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h> // atoi

int main (int argc, char** argv) {
    lseek(1, 2, SEEK_SET);
    char* file_data = mmap(NULL, 2, PROT_READ | PROT_WRITE, MAP_SHARED, 1, 0);
    char s[100] = "KEK";
    for (int i = 0; i < 3; ++i) {
        file_data[0] = s[i];
        msync(file_data, 2, MS_SYNC);
      //  sleep(1);
    }
    munmap(file_data, 2);

    return 0;
}

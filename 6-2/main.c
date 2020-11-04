#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

int main(int argc, char const** argv) {

    uint64_t size = 0;
    struct stat info;
    char s[PATH_MAX];

    while (fgets(s, PATH_MAX, stdin)) {
        char* end = memchr(s, '\n', PATH_MAX);
        *end = '\0';
        int res = lstat(s, &info);
        if (res != -1 && S_ISREG(info.st_mode) != 0) {
            size += info.st_size;
        }
    }

    printf("%ld", size);

    return 0;

}

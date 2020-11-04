#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

int main(int argc, char const** argv) {

    struct stat info;
    char file_name[PATH_MAX];

    while (fgets(file_name, PATH_MAX, stdin)) {
        char* end = memchr(file_name, '\n', PATH_MAX);
        *end = '\0';
        char help_name[PATH_MAX];
        int res = lstat(file_name, &info);
        if (res != -1 && S_ISLNK(info.st_mode) != 0) {
            realpath(file_name, help_name);
            printf("%s\n", help_name);
        }
        if (res != -1 && S_ISREG(info.st_mode) != 0) {
            strcpy(help_name, "link_to_");
            strcat(help_name, file_name);
            symlink(file_name, help_name);
        }
    }

    return 0;

}


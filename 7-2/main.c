#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <libgen.h>
#include <limits.h>


void process_file_r(
    char* file_path,
    char* file_name,
    struct stat* statbuf,
    long long int *size
) {
    if (S_ISREG(statbuf->st_mode)) {
        *size += statbuf->st_size;
    }
}


char calc_size(
    char* directory,
    void(*process)(char*, char*, struct stat*,
    long long int *size),
    char recursion,
    long long int *size
) {
    DIR *d;
    struct dirent *dir;
    d = opendir(directory);

    char full_path[PATH_MAX];

    struct stat statbuf;

    if (d) {
        while((dir = readdir(d)) != NULL) {
            strcpy(full_path, directory);
            strcat(full_path, dir->d_name);

            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
                int check = lstat(full_path, &statbuf);
                if (check != -1) {
                    process(full_path, dir->d_name, &statbuf, size);
                }
                if (check != -1 && recursion != 0 && S_ISDIR(statbuf.st_mode)) {
                    strcat(full_path, "/");
                    if(!calc_size(full_path, process, recursion, size)) {
                        return 0;
                    }
                }
            }
        }
    } else {
        return 0;
    }

    closedir(d);
    
    return 1;
}


int main (int argc, char** args) {
    long long int size = 0;
    char buff[PATH_MAX];
    strcpy(buff, args[1]);
    int n = strlen(buff);
    if (n > 0 && buff[n - 1] != '/') {
        strcat(buff, "/");
    }
    calc_size(buff, &process_file_r, 1, &size);
    printf("%lld", size);
    return 0;
}

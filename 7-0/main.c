#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

int main (int argc, char** args) {

    DIR *d;
    struct dirent *dir;
    d = opendir(args[1]);

    char full_path[4096];

    struct stat statbuf;

    int year = atoi(args[2]);
    int month = atoi(args[3]);
    int day = atoi(args[4]);

    struct tm time_start;

    memset(&time_start, 0, sizeof(time_start));

    time_start.tm_year = year - 1900;
    time_start.tm_mon = month - 1;
    time_start.tm_mday = day;
    time_start.tm_isdst = -1;

    time_t from = mktime(&time_start);

    if (d) {
        while((dir = readdir(d)) != NULL) {
           strcpy(full_path, args[1]);
           strcat(full_path, dir->d_name);
           int check = lstat(full_path, &statbuf);
           if (check != -1 && statbuf.st_mtime >= from) {
              printf("%s\n",  dir->d_name);
           }
        }
    }

    closedir(d);

    return 0;
    
}

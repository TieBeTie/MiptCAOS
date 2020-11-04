#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

int main (int argc, char** args) {

    DIR *d;
    struct dirent *dir;
    d = opendir(args[1]);

    char full_path[4096];

    struct stat statbuf;
    char time_string[255];

    struct tm time_struct;

    int year = atoi(args[2]);
    int month = atoi(args[3]);
    int day = atoi(args[4]);
    struct tm time_start;

    time_start.tm_yday = year;
    time_start.tm_mon = month;
    time_start.tm_mday = day;

    time_t from = mktime(&time_start);

    if (d) {
        while((dir = readdir(d)) != NULL) {
           strcpy(full_path, args[1]);
           strcat(full_path, dir->d_name);
           int check = lstat(full_path, &statbuf);
           if (check != -1) {
               time_t file_modified = localtime(&statbuf.st_mtime);
               if (statbuf.st_mtime - from >= 0) {
                   printf("%s\n",  dir->d_name);
               }
           }
        }
    }

    return 0;
}

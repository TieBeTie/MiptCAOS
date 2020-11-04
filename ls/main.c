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

char const* strperm(mode_t mode) {
    static char buff[16] = {0};
    int i = 0;
    // user
    if ((mode & S_IRUSR) == S_IRUSR) {
        buff[i] = 'r';
    } else {
        buff[i] = '-';
    }
    ++i;
    if ((mode & S_IWUSR) == S_IWUSR) {
      buff[i] = 'w';
    } else {
      buff[i] = '-';
    }
    ++i;
    if ((mode & S_IXUSR) == S_IXUSR) {
      buff[i] = 'x';
    }  else  {
      buff[i] = '-';
    }
    ++i;
    // group
    if ((mode & S_IRGRP) == S_IRGRP) {
      buff[i] = 'r';
    } else {
      buff[i] = '-';
    }
    ++i;
    if ((mode & S_IWGRP) == S_IWGRP) {
      buff[i] = 'w';
    } else {
      buff[i] = '-';
    }
    ++i;
    if ((mode & S_IXGRP) == S_IXGRP) {
      buff[i] = 'x';
    } else {
      buff[i] = '-';
    }
    ++i;
    // other
    if ((mode & S_IROTH) == S_IROTH) {
       buff[i] = 'r';
    } else {
      buff[i] = '-';
    }
    ++i;
    if ((mode & S_IWOTH) == S_IWOTH) {
      buff[i] = 'w';
    } else {
      buff[i] = '-';
    }
    ++i;
    if ((mode & S_IXOTH) == S_IXOTH) {
       buff[i] = 'x';
    } else {
       buff[i] = '-';
    }
    return local_buff;
}


void process_file(char* file_path, char* file_name, struct stat* statbuf) {
    char time_string[255];
    struct tm time_struct;

    strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%s", localtime(&statbuf->st_mtime));
    printf("%s\n", time_string);
}

void process_file_a(char* file_path, char* file_name, struct stat* statbuf) {
    printf("%s\t", file_name);
}

void process_file_R(char* file_path, char* file_name, struct stat* statbuf) {
    if (S_ISDIR(statbuf->st_mode)) {
      printf("\n\n%s\n\n", file_path);
    } else {
      printf("%s  ", file_name);
    }
}

void make_space(int a) {
    int k = 0;
    if (a == 0) {
        ++k;
    }
    while (a != 0) {
        ++k;
        a /= 10;
    }
    for (int i = 0; i < 8 - k; ++i) {
        printf(" ");
    }
}

char file_type(struct stat* statbuf) {

           switch (statbuf->st_mode & S_IFMT) {
             case S_IFBLK:
                return 'b';    // block device
             break;
             case S_IFCHR:
                return 'c'; // character device
             break;
             case S_IFDIR:
                return 'd'; // dir
              break;
             case S_IFIFO:
                return 'p'; // FIFO/pipe
             break;
             case S_IFLNK:
                return 'l'; // symlink
             break;
             case S_IFREG:
                return '-'; // reg file
             break;
             case S_IFSOCK:
                return 's'; //socket
             break;
           default:
                return 'D';
            break;
           }
}
void process_file_l(char* file_path, char* file_name, struct stat* statbuf) {
    printf("%c", file_type(statbuf));
    printf("%s ", strperm(statbuf->st_mode));
    printf("%ld ", statbuf->st_nlink);
    struct passwd* pswd = getpwuid(statbuf->st_uid);
    printf("%s ", pswd->pw_name);
    struct group* gr = getgrgid(statbuf->st_gid);
    printf("%s ", gr->gr_name);
    make_space(statbuf->st_size);
    printf("%ld ", statbuf->st_size);

    if (S_ISLNK(statbuf->st_mode)) {
      char real_name[4096];
      struct stat statbuf;
      realpath(file_path, real_name);

      printf("%s -> %s", file_name, real_name + (strlen(real_name) - strlen(basename(real_name))));
    } else {
      printf("%s", file_name);
    }
    puts("");
}

void ls(char* directory, void(*process)(char*, char*, struct stat*), char recursion) {
  DIR *d;
  struct dirent *dir;
  d = opendir(directory);

  char full_path[4096];

  struct stat statbuf;


  if (d) {
      while((dir = readdir(d)) != NULL) {
         strcpy(full_path, directory);
         strcat(full_path, dir->d_name);

         if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
           int check = lstat(full_path, &statbuf);
           if (check != -1) {
              process(full_path, dir->d_name, &statbuf);
           }
           if (check != -1 && recursion != 0 && S_ISDIR(statbuf.st_mode)) {
              strcat(full_path, "/");
              ls(full_path, process, recursion);
           }
         }
      }
  }
}

int main (int argc, char** args) {
    ls(args[1], &process_file_l, 0);
    printf("\n");
    return 0;
}

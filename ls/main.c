/* my own ls implementation */
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <libgen.h>
#include <limits.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

/* result structure for ls -l flag */
struct l_ls_result {
    int capacity;            // current capacity
    int count;               // output count
    int max_size_len;        // max size string
    int max_link_len;        // max link count string
    int max_user_len;        // max username length
    int max_group_len;       // max length of group name
    int max_file_name_len;   // max length of file name string, for aligment
    char** permissions;      // file permissions
    char** links;            // links count
    char** users;            // users
    char** groups;           // groups
    char** sizes;            // sizes
    char** names;            // file names
};

/* clear string array */
void clear_string_array (char** arr, int n) {
    for (int i = 0; i < n; ++i) {
        if (arr[i] != NULL) {
            free(arr[i]);
        }
    }
}

/* clear l_ls_result struct data from memory */
void clear_l_ls_result_struct (struct l_ls_result* data) {
    if (data->permissions != NULL) {
        clear_string_array(data->permissions, data->count);
        free(data->permissions);
    }
    if (data->links != NULL) {
        clear_string_array(data->links, data->count);
        free(data->links);
    }
    if (data->users != NULL) {
        clear_string_array(data->users, data->count);
        free(data->users);
    }
    if (data->groups != NULL) {
        clear_string_array(data->groups, data->count);
        free(data->groups);
    }
    if (data->sizes != NULL) {
        clear_string_array(data->sizes, data->count);
        free(data->sizes);
    }
    if (data->names != NULL) {
        clear_string_array(data->names, data->count);
        free(data->names);
    }
    memset(data, 0, sizeof(struct l_ls_result));
}


struct l_ls_result* create_l_ls_result_struct (int capacity) {

    struct l_ls_result* res = (struct l_ls_result*)malloc(sizeof(struct l_ls_result));
    if (res == NULL) {
        return NULL;
    }
    memset(res, 0, sizeof(struct l_ls_result));

    res->capacity = capacity;
    res->count = 0;
    res->permissions = (char**)malloc(capacity * sizeof(char**));
    res->links = (char**)malloc(capacity * sizeof(char**));
    res->users = (char**)malloc(capacity * sizeof(char**));
    res->groups = (char**)malloc(capacity * sizeof(char**));
    res->sizes = (char**)malloc(capacity * sizeof(char**));
    res->names = (char**)malloc(capacity * sizeof(char**));
    /* if we have some errors, we will remove struct */
    if (
        res->permissions == NULL ||
        res->links == NULL ||
        res->users == NULL ||
        res->groups == NULL ||
        res->sizes == NULL ||
        res->names == NULL
    ) {
        clear_l_ls_result_struct(res);
        free(res);
        return NULL;
    }

    return res;

}

/* reallocate memory */
struct l_ls_result* reallocate_l_ls_result_struct (
    struct l_ls_result* res,
    int capacity
) {

    char** permissions = (char**)realloc(res->permissions, capacity * sizeof(char**));
    if (permissions == NULL) {
        return NULL;
    }
    char** links = (char**)realloc(res->links, capacity * sizeof(char**));
    if (links == NULL) {
        return NULL;
    }
    char** users = (char**)realloc(res->users, capacity * sizeof(char**));
    if (permissions == NULL) {
        return NULL;
    }
    char** groups = (char**)realloc(res->groups, capacity * sizeof(char**));
    if (groups == NULL) {
        return NULL;
    }
    char** sizes = (char**)realloc(res->sizes, capacity * sizeof(char**));
    if (sizes == NULL) {
        return NULL;
    }
    char** names = (char**)realloc(res->names, capacity * sizeof(char**));
    if (names == NULL) {
        return NULL;
    }

    res->permissions = permissions;
    res->links = links;
    res->users = users;
    res->groups = groups;
    res->sizes = sizes;
    res->names = names;

    res->capacity = capacity;

    return res;

}

char* strperm (mode_t mode) {
    int i = 0;
    static char buff[16] = {0};
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
    ++i;
    buff[i] = '\0';
    return buff;
}


int max(int x, int y) {
    if (x > y) {
        return x;
    } else {
        return y;
    }
}


char file_type (struct stat* statbuf) {
     switch (statbuf->st_mode & S_IFMT) {
       case S_IFBLK:
          return 'b'; // block device
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


void process_file_a (
    char* file_path,
    char* file_name,
    struct stat* statbuf,
    void* result
) {
    printf("%s\t", file_name);
}


void process_file_R (
    char* file_path,
    char* file_name,
    struct stat* statbuf,
    void* result
) {
    if (S_ISDIR(statbuf->st_mode)) {
      printf("\n\n%s\n\n", file_path);
    } else {
      printf("%s  ", file_name);
    }
}


void process_file_l (
    char* file_path,
    char* file_name,
    struct stat* statbuf,
    void* result
) {
    /* file is hidden */
    if (file_name[0] == '.') {
        return;
    }

    struct l_ls_result* out = (struct l_ls_result*)result;

    if (out->count == out->capacity) {
        reallocate_l_ls_result_struct(out, out->capacity * 2);
    }

    /* permission string */
    char permissions[11];
    permissions[0] = file_type(statbuf);
    permissions[1] = '\0';
    char* perm = strperm(statbuf->st_mode);
    strcat(permissions, perm);
    int perm_len = strlen(permissions);
    out->permissions[out->count] = (char*)malloc((perm_len + 1) * sizeof(char));
    strcpy(out->permissions[out->count], permissions);

    /* links count */
    out->links[out->count] = (char*)malloc((24) * sizeof(char));
    sprintf(out->links[out->count], "%ld", statbuf->st_nlink);
    out->max_link_len = max(out->max_link_len, strlen(out->links[out->count]));

    /* username */
    struct passwd* pswd = getpwuid(statbuf->st_uid);
    out->users[out->count] = (char*)malloc((34) * sizeof(char));
    strcpy(out->users[out->count], pswd->pw_name);
    out->max_user_len = max(out->max_user_len, strlen(out->users[out->count]));

    /* group name */
    struct group* gr = getgrgid(statbuf->st_gid);
    out->groups[out->count] = (char*)malloc((18) * sizeof(char));
    strcpy(out->groups[out->count], gr->gr_name);
    out->max_group_len = max(out->max_group_len, strlen(out->groups[out->count]));

    /* file size */
    out->sizes[out->count] = (char*)malloc((24) * sizeof(char));
    sprintf(out->sizes[out->count], "%ld", statbuf->st_size);
    out->max_size_len = max(out->max_size_len, strlen(out->sizes[out->count]));

    if (S_ISLNK(statbuf->st_mode)) {
      char real_name[2 * PATH_MAX + 5];
      out->names[out->count] = (char*)malloc((2 * PATH_MAX + 5) * sizeof(char));
      struct stat statbuf;
      realpath(file_path, real_name);
      sprintf(out->names[out->count], "%s -> %s", file_name, real_name + (strlen(real_name) - strlen(basename(real_name))));
    } else {
      out->names[out->count] = (char*)malloc((PATH_MAX + 1) * sizeof(char));
      sprintf(out->names[out->count], "%s", file_name);
    }

    out->max_file_name_len = max(out->max_file_name_len, strlen(out->names[out->count]));
    ++(out->count);

}


void ls (
    char* directory,
    void(*process)(char*, char*, struct stat*, void*),
    void* result,
    char recursion
) {
    DIR *d;
    struct dirent *dir;
    d = opendir(directory);
    if (d == NULL) {
        return;
    }
    char full_path[PATH_MAX];

    struct stat statbuf;

    if (d) {
        while((dir = readdir(d)) != NULL) {
           strcpy(full_path, directory);
           strcat(full_path, dir->d_name);

           if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
             int check = lstat(full_path, &statbuf);
             if (check != -1) {
                process(full_path, dir->d_name, &statbuf, result);
             }
             /* check if we need work recursively f.e. -R */
             if (check != -1 && recursion != 0 && S_ISDIR(statbuf.st_mode)) {
                strcat(full_path, "/");
                ls(full_path, process, result, recursion);
             }
           }
        }
    }
}

void print_align_left(char* s, int size) {
    int len = strlen(s);
    printf("%s", s);
    for (int i = len; i  < size; ++i) {
        printf(" ");
    }
}

void print_align_right(char* s, int size) {
    int len = strlen(s);
    for (int i = len; i  < size; ++i) {
        printf(" ");
    }
    printf("%s", s);
}

void print_result_ls_l (struct l_ls_result* out) {
    for (int i = 0; i < out->count; ++i) {
        printf("%s ", out->permissions[i]);
        print_align_right(out->links[i], out->max_link_len);
        printf(" ");
        print_align_left(out->users[i], out->max_user_len);
        printf(" ");
        print_align_left(out->groups[i], out->max_group_len);
        printf(" ");
        print_align_right(out->sizes[i], out->max_size_len);
        printf(" ");
        print_align_left(out->names[i], out->max_file_name_len);
        puts("");
    }
}

int main (int argc, char** args) {

    struct l_ls_result* out = create_l_ls_result_struct(1);
    char path[PATH_MAX + 1] = "";
    if (argc == 1) {
        if (getcwd(path, sizeof(path)) == NULL) {
            perror("Bad input");
            exit(1);
        }
    } else {
        strcpy(path, args[1]);
    }
    int path_len = strlen(path);
    if (path_len != 0 && out != NULL) {
        struct stat statbuf;
        int check = lstat(path, &statbuf);
        if (check != -1) {
            if (S_ISDIR(statbuf.st_mode)) {
                /* we have a directory */
                if (path[path_len - 1] != '/') {
                    strcat(path, "/");
                }
                ls(path, &process_file_l, out, 0);
                print_result_ls_l(out);
            } else {
                /* we have a file */
                process_file_l(path, path, &statbuf, out);
                print_result_ls_l(out);
            }
            clear_l_ls_result_struct(out);
        } else {
            /* we have a file */
            perror("");
            exit(1);
        }
    }

    return 0;

}

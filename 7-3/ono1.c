void remove_extra_slashes(char * path, int* n) {

    int i = 0;
    char prev = '\0';
    int shift = 0;

    while (path[i] != '\0') {

        if (path[i] == '/' && prev == '/') {
            ++shift;
        }

        prev = path[i];
        ++i;
        path[i - shift] = path[i];

    }

    *n -= shift;

}

void remove_dot_slash(char * path, int* n) {

    int i = 0;
    char prev = '\0';
    char prev_prev = '\0';
    int shift = 0;

    while (path[i] != '\0') {

        if (path[i] == '/' && prev == '.' && prev_prev != '.') {
            shift += 2;
        }

        prev_prev = prev;
        prev = path[i];
        ++i;
        path[i - shift] = path[i];

    }

    *n -= shift;

}

void process_dots(char * path, int* n) {

  int i = 0;
  char prev = '\0';

  int shift = 0;

    while (path[i] != '\0') {

        if (path[i] == '.' && prev == '.') {
            char newprev = path[i + 1];
            int j = i - shift;
            int k = 1;
            int z = 0;
            while(j >= 0 && z < 2) {
                --j;
                ++k;
                if (path[j] == '/') {
                    ++z;
                }
            }
            shift += k;
            prev = newprev;
        }

        prev = path[i];
        ++i;
        path[i - shift] = path[i];

    }

    *n -= shift;

}

int my_strlen(char * path) {

    int i = 0;

    while (path[i] != '\0') {
        ++i;
    }
    
    return i;

}

void normalize_path(char * path) {
    int n = my_strlen(path);
    remove_extra_slashes(path, &n);
    remove_dot_slash(path, &n);
    process_dots(path, &n);
    path[n] = '\0';
}

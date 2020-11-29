void remove_i(char * path, int i, int* n) {
    --*n;
    for (int j = i; j < *n; ++j) {
        path[j] = path[j + 1];
    }
    path[*n] = '\0';
}

void remove_extra_slashes(char * path, int* n) {
    int i = 0;
    char prev = '\0';
    while (path[i] != '\0') {

        if (path[i] == '/' && prev == '/') {
            remove_i(path, i, n);
        } else {
            prev = path[i];
            ++i;
        }
    }
}

void remove_dot_slash(char * path, int* n) {
  int i = 0;
  char prev = '\0';
  char prev_prev = '\0';
  while (path[i] != '\0') {
      if (path[i] == '/' && prev == '.' && prev_prev != '.') {
          char newprev = path[i + 1];
          remove_i(path, i - 1, n);
          remove_i(path, i - 1, n);
          prev = newprev;
      } else {
          prev_prev = prev;
          prev = path[i];
          ++i;
      }
  }
}

void process_dots(char * path, int* n) {
  int i = 0;
  char prev = '\0';
  while (path[i] != '\0') {

      if (path[i] == '.' && prev == '.') {
          char newprev = path[i + 1];
          int j = i;
          int k = 1;
          int z = 0;
          while(j >= 0 && z < 2) {
              --j;
              ++k;
              if (path[j] == '/') {
                  ++z;
              }
          }
          i = j;
          for (int j = 0; j < k; ++j) {
              remove_i(path, i, n);
          }
          prev = newprev;
      } else {
          prev = path[i];
          ++i;
      }
  }
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
}

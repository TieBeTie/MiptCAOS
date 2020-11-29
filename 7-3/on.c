#include <stdlib.h>

void remove_pos(int* pos, int k, char * path, int* n) {
  if (k == 0) {
    return;
  }
  int j = 0;
  int shift_left = 0;
  for (int i = 0; i < *n; ++i) {
      if (i == pos[j]) {
          ++j;
          ++shift_left;
      } else {
          path[i - shift_left] = path[i];
      }
  }
  *n -= shift_left;
  path[*n] = '\0';
}

void remove_extra_slashes(char * path, int* n) {
    int i = 0;
    char prev = '\0';
    int* pos = (int*)malloc(*n * sizeof(int));
    int k_pos = 0;
    while (path[i] != '\0') {
        if (path[i] == '/' && prev == '/') {
            pos[k_pos++] = i;
        }
        prev = path[i];
        ++i;
    }
    remove_pos(pos, k_pos, path, n);
    free(pos);
}

void remove_dot_slash(char * path, int* n) {

  int i = 0;
  char prev = '\0';
  char prev_prev = '\0';

  int* pos = (int*)malloc(*n * sizeof(int));
  int k_pos = 0;

  while (path[i] != '\0') {
      if (path[i] == '/' && prev == '.' && prev_prev != '.') {
          pos[k_pos++] = i - 1;
          pos[k_pos++] = i;
      }
      prev_prev = prev;
      prev = path[i];
      ++i;
  }

  remove_pos(pos, k_pos, path, n);
  free(pos);

}

void process_dots(char * path, int* n) {
  int i = 0;
  char prev = '\0';

  int* r_pos = (int*)malloc(*n * sizeof(int));
  int k_pos = 0;

  int now = *n;
  int to_be_removed = 0;
  while (now >= 0) {
      if (now >= 3 && path[now] == '/' && path[now - 1] == '.') {
          ++to_be_removed;
          now -= 3;

      } else if (to_be_removed != 0) {
          for (int i = now + 3 * to_be_removed; i > now; --i) {
              r_pos[k_pos++] = i;
          }
          int z = 0;

          while(now >= 0 && z != to_be_removed + 1) {
              if (path[now] == '/') {
                 ++z;
              }
              r_pos[k_pos++] = now;
              --now;
          }

          if (path[r_pos[k_pos - 1]] == '/') {
              --k_pos;
              ++now;
          }

          to_be_removed = 0;
      } else {
        --now;
      }
  }

  int* pos = (int*)malloc(*n * sizeof(int));

  for (int i = 0; i < k_pos; ++i) {
      pos[i] = r_pos[k_pos - i - 1];
  }

  free(r_pos);
  remove_pos(pos, k_pos, path, n);
  free(pos);

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

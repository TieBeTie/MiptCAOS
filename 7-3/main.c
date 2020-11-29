#include <stdio.h>

extern void normalize_path(char * path);

int main() {
    char path[4096] = "/var/../log/../lib/./ejexec/../";
  //  char path2[4096] = "i/./jjj/////ggg/../../file";
    normalize_path(path);
    printf("%s\n", path);
}

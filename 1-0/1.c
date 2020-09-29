#include <stdio.h>
#include <stdlib.h>

const int SYSTEM_BASE = 27;

int main (int argc, char** argv) {

  float x;
  int y;

  int z = strtol(argv[1], NULL, SYSTEM_BASE);
  scanf("%f %x", &x, &y);

  printf("%.3f", x + z + y);

  return 0;
}
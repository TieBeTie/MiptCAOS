#include <stdio.h>
#include <math.h>

extern
double my_sin(double x);

int main () {
  printf("my_sin: %.3lf\n", my_sin(2.0));
  printf("sin: %.3lf", sin(2.0));
  return 0;
}

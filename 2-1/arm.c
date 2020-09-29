#include <stdio.h>


extern
int f(int a, int b, int c, int x);


int main () {
   printf("%d\n", f(1, 2, 3, 6));
   return 0;
}

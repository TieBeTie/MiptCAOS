#include <stdio.h>
extern float dot_product(int N, const float *A, const float *B);
int main(){
   int n;
   scanf("%d", &n);
   float a[100];
   float b[100];
   for (int i = 0; i < n; ++i) {
       scanf("%f %f", a + i, b + i);
   }
   float res = 0;
   for (int i = 0; i < n; ++i) {
       res += a[i] * b[i];
   }
   printf("%.3f %.3f", res, dot_product(n, a, b));
   return 0;
}

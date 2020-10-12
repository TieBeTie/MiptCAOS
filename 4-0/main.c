#include <stdio.h>

extern
int summ(int N, const int* A, const int* B, int* R);

int main() {
    int a[4];
    int b[4];
    for (int i = 0; i < 4; ++i)
       scanf("%d", a + i);
    for (int i = 0; i < 4; ++i)
       scanf("%d", b + i);
    int r[4];
    printf("%d\n", summ(4, a, b, r));
    for (int i = 0; i < 4; ++i)
       printf("%d ", r[i]);
    return 0;
}

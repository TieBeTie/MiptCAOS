#include <stdio.h>

extern
int solve (int A, int B, int C, int D);
int main () {
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    printf("%d", solve(a, b, c, d));
    return 0;
}

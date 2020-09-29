#include <stdio.h>

extern
int summ (int x0, int N, int *X);

int main () {
    int res = 0;
    int n;
    int x0;
    scanf("%d", &x0);
    scanf("%d", &n);
    int a[100];
    for (int i = 0; i < n; ++i) {
       scanf("%d", a + i);
    }
    printf("%d", summ(x0, n, a));
    return 0;
}

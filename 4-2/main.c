#include <stdio.h>

extern int merge_sort (int from, int to, const int *in, int *out);

extern void merge (int* in1, int* in2, int n1, int n2, int *out);

int main () {
    int n, m;
    int a[200];
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", a + i);
    }
    int d[20000];
    printf("%d\n", merge_sort(0, n - 1, a, d));
    int c[4000];
    //merge(a, a + n - 1, n - 1, 1, a);
    for (int i = 0; i < n; ++i) {
        printf("%d ", *(d + i));
    }
    return 0;
}

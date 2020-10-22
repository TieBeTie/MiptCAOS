#include <stdio.h>

extern int merge_sort (int from, int to, const int *in, int *out);

extern void merge (int* in1, int* in2, int n1, int n2, int *out);

int main () {
    int n;
    int a[200];
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", a + i);
    }
    int d[200];
    merge_sort(0, n, a, d);
    for (int i = 0; i < n; ++i) {
        printf("%d ", *(d + i));
    }
    return 0;
}

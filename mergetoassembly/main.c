#include <stdlib.h>

void  merge(int *a, int l, int r) {
    int mid = l + (r - l) / 2;
    int i = 0;
    int j = 0;
    int res[r - l];
    while(l + i < mid && mid + j < r) {
        if (a[l+i] < a[mid + j]) {
            res[i + j] = a[l + i];
            i++;
        } else {
            res[i + j] = a[mid + j];
            j++;
        }
    }
    while(l + i < mid) {
        res[i + j] = a[l + i];
        i++;
    }
    while(mid + j < r) {
        res[i + j] = a[mid + j];
        j++;
    }
    for (int z = 0; z < r - l; z++){
        a[l + z] = res[z];
    }
}

void mergeSort(int *a, int l, int r) {
    if (l + 1 >= r)
        return;
    int mid = l + (r - l) / 2;
    mergeSort(a, l, mid);
    mergeSort(a, mid, r);
    merge(a, l, r);
}

int main() {
    int *a = (int*)malloc(sizeof(int) * 4);
    for (int i = 0; i < 10; i++)
        a[i] = 0;
    mergeSort(a, 0, 10);
    free(a);
    return 0;
}

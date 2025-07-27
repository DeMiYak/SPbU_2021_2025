#include <stdio.h>
#include "BinFunc.h"

int cmp(const int *a, const int *b) {
    if (*a == *b)return 0;
    if (*a > *b)return 1;
    return -1;
}

int main() {
    size_t n;
    scanf("%Iu", &n);
    int arr[n];
    for (int i = 0; i < n; ++i) {
        scanf("%i", &arr[i]);
    }
    int find;
    scanf("%i", &find);
    int *res = BinFind(arr, &find, sizeof(int), n, cmp);
    printf("14.3 a=%i\n", *res);
    res = UpperBound(arr, &find, sizeof(int), n, cmp);
    printf("14.3 b=%i", res - arr);
    return 0;
}

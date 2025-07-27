#include <stdio.h>

void SumNum(int n, int p, int *sum, int *k) {
    *sum = 0;
    *k = 0;
    while (n) {
        *sum += n % p;
        n /= p;
        ++*k;
    }
}

int main() {
    int n, p, sum = 0, k = 0;
    scanf("%d%d", &n, &p);
    SumNum(n, p, &sum, &k);
    printf("sum=%i k=%i", sum, k);
}

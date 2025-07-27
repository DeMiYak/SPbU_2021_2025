#include <stdio.h>

int S(int n, int p) {
    int sum = 0;
    while (n) {
        sum += n % p;
        n /= p;
    }
    return sum;
}

int DR(int n, int p) {
    while (n>=p){
        n= S(n,p);
    }
    return n;
}

int main() {
    int n, p;
    scanf("%i%i", &n, &p);
    printf("%i", DR(n, p));
    return 0;
}
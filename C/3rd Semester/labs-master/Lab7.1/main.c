#include <stdio.h>

int main() {
    int n;
    int sum = 0;
    int sys = 10;
    scanf("%i", &n);
    while (n > 0) {
        sum += n % sys;
        n /= sys;
    }
    printf("%i", sum);
}

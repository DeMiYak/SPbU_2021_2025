#include <stdio.h>

int main() {
    int n;
    scanf("%i", &n);
    if (n % 4 == 0 && !(n % 100 == 0 && n % 400 != 0))
        printf("366");
    else
        printf("365");
}

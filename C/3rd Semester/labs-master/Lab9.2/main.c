#include <stdio.h>

void IfSwap(int *a, int *b) {
    if (*a > *b) {
        int temp = *a;
        *a = *b;
        *b = temp;
    }
}

int main() {
    int a,b;
    scanf("%i%i",&a,&b);
    IfSwap(&a,&b);
    printf("a = %i\nb = %i",a,b);
}

#include <stdio.h>
#include "nums.h"


int main() {
    int p;
    printf("p=");
    scanf("%i", &p);
    printf("iter:\n");
    NumPrint(p);
    printf("\nrecursion:\n");
    RecNumPrint(p, 0);
    printf("\nrevers recursion:\n");
    RecNumPrintRevers(p);
}

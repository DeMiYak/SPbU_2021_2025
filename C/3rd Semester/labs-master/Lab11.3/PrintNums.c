#include <stdio.h>
#include "nums.h"

const char num[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

void NumPrint(int p) {
    for (int i = p - 1; i >= 0; --i) {
        printf("%c ", num[i]);
    }
    printf("\n");
}

void RecNumPrintRevers(int p) {
    if (p == 0) {
        printf("\n");
        return;
    }
    printf("%c ", num[p - 1]);
    RecNumPrintRevers(p - 1);
}


void RecNumPrint(int p, int i) {
    if (i == p) {
        printf("\n");
        return;
    }
    printf("%c ", num[i]);
    RecNumPrint(p, i + 1);
}

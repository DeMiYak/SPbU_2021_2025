#include <stdio.h>
#include "head.h"

int main() {
    size_t limit = 100;
    char string[limit];
    gets(string);
    removeSpace(string);
    printf("|%s|",string);
    return 0;
}

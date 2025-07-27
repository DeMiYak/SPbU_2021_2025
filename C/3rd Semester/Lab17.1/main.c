#include <stdio.h>
#include "DeleteSpace.h"
int main() {
    size_t len = 100;
    char s[len];
    gets(s);
    DeleteSpace(s);
    printf("|%s|",s);
    return 0;
}

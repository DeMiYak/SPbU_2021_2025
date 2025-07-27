#include<stdio.h>
#include<stdlib.h>
#include"head.h"
#include<string.h>
#include<stddef.h>

/* 10
0123456789 */

int main()
{
    size_t limit = 100;
    char *src = malloc(sizeof(char)*11);
    char *cpy = malloc(sizeof(char)*limit);
    src = "0123456789";

    subtract(src, cpy, 4, 3);
    printf("|%s|\t%i\n", cpy, strcmp(cpy, "456"));

    subtract(src, cpy, 4, 100);
    printf("|%s|\t%i\n", cpy, strcmp(cpy, "456789"));

    subtract(src, cpy, 4, 0);
    printf("|%s|\t%i\n", cpy, strcmp(cpy, "456789"));

    subtract(src, cpy, 10, 3);
    printf("|%s|\t%i\n", cpy, strcmp(cpy, ""));

    subtract(src, cpy, -4, 2);
    printf("|%s|\t%i\n", cpy, strcmp(cpy, "67"));

    subtract(src, cpy, -4, 0);
    printf("|%s|\t%i\n", cpy, strcmp(cpy, "6789"));

    subtract(src, cpy, -4, 5);
    printf("|%s|\t%i\n", cpy, strcmp(cpy, "6789"));

    subtract(src, cpy, -12, 5);
    printf("|%s|\t%i\n", cpy, strcmp(cpy, "012"));

    subtract(src, cpy, -100, 3);
    printf("|%s|\t%i\n", cpy, strcmp(cpy, ""));

    subtract(src, cpy, 4, -2);
    printf("|%s|\t%i\n", cpy, strcmp(cpy, "34"));

    subtract(src, cpy, 4, -100);
    printf("|%s|\t%i\n", cpy, strcmp(cpy, "01234"));

    subtract(src, cpy, 11, -3);
    printf("|%s|\t%i\n", cpy, strcmp(cpy, "9"));

    subtract(src, cpy, 11, -2);
    printf("|%s|\t%i\n", cpy, strcmp(cpy, ""));

    subtract(src, cpy, -3, -3);
    printf("|%s|\t%i\n", cpy, strcmp(cpy, "567"));

    subtract(src, cpy, -3, -10);
    printf("|%s|\t%i\n", cpy, strcmp(cpy, "01234567"));

    free(src);
    free(cpy);
    return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"head.h"

void arrFill(char *src, size_t limit)
{
    char *ptr = src, *end = src + limit;
    for(; ptr < end; ++ptr)
    {
        scanf("%c", ptr);
        printf("%c, %Iu\n", *ptr, ptr - src);
        if(*ptr == '\n') break;
    }
    *ptr = '\0';
}

size_t transferArr(char *src, char **cpy)
{
    char **ptrCpy = cpy;
    size_t i = 0;
    for(char *ptr = strtok(src, " ,.;:-!?"); ptr != NULL; ptr = strtok(NULL, " ,.;:-!?"))
    {
        puts(ptr);
        *ptrCpy = ptr;
        printf("%s %Iu\t\n\n", *ptrCpy, i);
        ++ptrCpy;
        ++i;
    }
    **ptrCpy = NULL;
    return i;
}

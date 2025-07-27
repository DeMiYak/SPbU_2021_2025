#include<stdio.h>
#include"head.h"

void removeSpace(char *src)
{
    char *ptrWrite = src;
    char *ptrRead = src;
    while(*ptrRead == ' ')++ptrRead;
    printf("|%s|\n", src);
    for(; *ptrRead != '\0'; ++ptrRead){
        while(*ptrRead == ' ' && *(ptrRead + 1) == ' '){
            ++ptrRead;
        }
        *ptrWrite = *ptrRead;
        ++ptrWrite;
    }
    if(ptrWrite != src && *(ptrWrite - 1) == ' ') *(ptrWrite - 1) = '\0';
    else *ptrWrite = '\0';
}

void arrFill(char *src, size_t limit)
{
    char *ptrFill = src, *end = src + limit;
    {
    //    char temp;
    //    scanf("%c", &temp);
    }
    scanf("%c", ptrFill);
    while(*ptrFill != '\n' && ptrFill < end){
        ++ptrFill;
        scanf("%c", ptrFill);
        printf("%c ! %Iu\n", *ptrFill, ptrFill - src);
    }
    *ptrFill = '\0';
}

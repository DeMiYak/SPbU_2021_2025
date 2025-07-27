#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>
#include"head.h"


void subtract(char *src, char *cpy, long n, long m)
{
    long limit = strLen(src);
    if (n < 0)n += limit;
    if (m < 0)
    {
        n += m + 1;
        m = -m;
    }

    if (n < 0)
    {
        m += n;
        n = 0;
    }

    if (/*(size_t)*/ n >= limit || m < 0)
    {
        cpy[0] = '\0';
        return;
    }

    if(n + m >= limit || m == 0)
    {
        m = limit - n;
    }
    arrSub(src, cpy, n, m);
}


/*
void arrFill(char *src, size_t limit)
{
    char *ptr = src, *end = src + limit;
    {
    //    char temp;
    //    scanf("%c", &temp);
    }
    scanf("%c", ptr);
    for(;*ptr != '\n' && ptr < end; ++ptr)
    {
        scanf("%c", ptr);
    }
    *ptr = '\0';
}
*/


void arrSub(char *src, char *cpy, size_t n, size_t m)
{
    char *ptrRead = src + n;
    char *ptrWrite = cpy;
    for(; *ptrRead != '\0' && m > 0; --m)
    {
        *ptrWrite = *ptrRead;
        ++ptrWrite;
        ++ptrRead;
    }
    *ptrWrite = '\0';
}

long strLen(const char *src)
{
    const char *ptr = src;
    long len = 0;
    for(; *ptr != '\0'; ++ptr, ++len);
    return len;
}

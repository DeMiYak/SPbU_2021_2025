#include<stdio.h>
#include"sup.h"

size_t arrFill(char *src, size_t length)
{
    char *ptr = src, *end = src + length;
    size_t count = 0;
    for(; ptr < end; ++ptr)
    {
        scanf("%c", ptr);
        if(*ptr == '\n')
        {
            *ptr = '\0';
            break;
        }
        ++count;
    }
    return count;
}

size_t findc(char *src, size_t length, char letter)
{
    char *ptr = src, *end = src + length;
    size_t letters = 0;
    int temp = 0;
    for(; ptr < end; ++ptr) // Берём символ и проверяем на соответствие
    {
        if((*ptr == ' ' || *ptr ==  ',' || *ptr == '.' || *ptr  == ';' || *ptr  == ':' || *ptr == '!' || *ptr == '?') && ptr < end) // Условие проверки на наличие
        {
            temp = 0;
            printf("\n0\n");
            int d;
            scanf("%d", &d);
        }
        if(*ptr == letter && temp == 0)
            {
                temp = 1;
                ++letters;
                printf("\nletters = %Iu, ptr =  %c, curr = %Iu\n", letters, *ptr, ptr - src);
            }
    }
    *ptr = '\0';
    return letters;
}

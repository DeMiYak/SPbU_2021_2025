#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>

char *writeLine()
{
    size_t limit = 100;
    char *line = malloc(limit);
    if(!line) return NULL;
    char *ptr = line;
    while(scanf("%c", ptr))
    {
        if(*ptr == '\n')
        {
            break;
        }
        ++ptr;
        if(ptr - line + 1 == limit)
        {
            limit *= 2;
            line = realloc(line, sizeof(limit));
        }
    }
    *ptr = '\0';
    return line;
}

size_t readLine(char *line, char key)
{
    char *ptr = line;
    size_t count = 0;
    size_t isWord = 0;
    for(; *ptr != '\0'; ++ptr)
    {
        if(*ptr == ';' || *ptr == ' ' || *ptr == '.' || *ptr == ',' || *ptr == '-' || *ptr == '|' || *ptr == ':' || *ptr == '!' || *ptr == '?') // Ввод разделителя
        {
            isWord = 0;
        }
        else
        {
            if(!isWord && *ptr == key) // Проверка на первое вхождение символа
            {
                isWord = 1;
                count++;
            }
            isWord = 1;

        }
        printf("ptr = %Iu, ptr = %c, count = %Iu, isWord = %Iu\n", ptr - line, *ptr, count, isWord);
    }
    printf("ptr = %c, ptr = %Iu", *ptr, ptr - line);
    return count;
}

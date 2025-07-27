#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>

char *writeLine()
{
    size_t limit = 100;
    char *line = malloc(sizeof(limit));
    if(!line) return NULL;
    char *ptr = line;
    while(scanf("%c", ptr))
    {
        if(*ptr == '\n')
        {
            *ptr = '\0';
            break;
        }
        ++ptr;
        if(ptr - line == limit)
        {
            limit *= 2;
            line = realloc(line, sizeof(limit));
        }
    }
    return line;
}

size_t readLine(char *line, char key)
{
    char *ptr = line;
    size_t count = 0;
    int temp = 0;
    for(; *ptr != '\0'; ++ptr)
    {
        if(*ptr == ';' || *ptr == ' ' || *ptr == '.' || *ptr == ',' || *ptr == '-' || *ptr == '|' || *ptr == ':' || *ptr == '[' || *ptr == ']')
        {
            temp = 0;
        }
        if(*ptr == key && temp == 0)
        {
            temp = 1;
            count++;
        }
    }
    return count;
}

#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>

size_t strnum(const char *filename, int key)
{
    FILE *f = freopen(filename, "r", stdin);
    int d;
    char c;
    size_t currLine = 1, rightLine = 0;
    while(scanf("%d%c", &d, &c) > 0)
    {
        if(d == key) // Проверка на первое вхождение искомого числа (используем break)
        {
            rightLine = currLine;
            break;
        }
        if(c == '\n') currLine++;
    }
    fclose(f);
    return rightLine;
}

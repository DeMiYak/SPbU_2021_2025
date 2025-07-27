#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>
#include<string.h>

/**
// 1
size_t strnum(const char *filename)
{
    FILE *f = fopen(filename, "r");
    if(!f) exit(1);
    size_t b_cap = 0;
    size_t b_pos = 0;
    char *buffer = NULL;
    int c;
    do
    {
        if(b_pos >= b_cap)
        {
            b_cap += 1000;

            char *buffer2 = realloc(buffer, b_cap);
            if(!buffer2) exit(0);
            buffer2 = buffer;
        }
        c = fgetc(f);
        if(c == EOF || c == '\n')
            buffer[b_pos] = '\0';
        else buffer[b_pos] = c;
        ++b_pos;
    }
    while(c != EOF && c != '\n');


    char *snum = strtok(buffer, " ");
    double max = -1/0.0;
    size_t curr = 0, ret = 0;
    while(snum != NULL)
    {
        ++curr;
        double num;
        while(sscanf(snum, "%lf", &num))
        {
            if(num > max)
            {
                max = num;
                ret = curr;
            }
        }
        snum = strtok(NULL, " ");
    }
    fclose(f);
    return ret;
}
*/

// 3
size_t strnum(const char *filename)
{
    FILE *f = freopen(filename, "r", stdin);
    double x, max = -1/0.0;
    char c;
    size_t currStr = 1, maxStr = 0;
    while(scanf("%lf%c", &x, &c) > 0)
    {
        // printf("%lf\n%c\n", x, c);
        if(x > max)
        {
            max = x;
            maxStr = currStr;
        }
        if(c == '\n') currStr++;
    }
    // printf("max = %lf\nmaxStr = %Iu", max, maxStr);

    fclose(f);
    return maxStr;
}

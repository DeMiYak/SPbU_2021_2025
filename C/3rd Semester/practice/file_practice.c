#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>
#include<math.h>

int main()
{
    FILE *f = fopen("fillet.txt", "r");
    double x, max = -1/0.0;
    char c;
    size_t countMax = 0, countCurr = 0;
    while(fscanf(f, "%lf%c", &x, &c) > 0)
    {
        if(x > max)
        {
            max = x;
            countMax = countCurr;
        }
        if(c == '\n') countCurr++;
    }
    printf("max = %lf, line = %Iu", max, countMax);
    fclose(f);
    return 0;
}

#include<stdio.h>
#include"head.h"
#include<stddef.h>


void assigndbl(size_t n, double *c)
{
    double *p, *e;
    for(p = c, e = p + n; p < e; ++p)
        scanf("%lf", p);
}

void *binsearch(size_t n, double *c, double x)
{
    double *p = c, *e = c + n;
    while(n)
    {
        double *g = (p + n - 1)/2;

        if(*g == x) return g;

        if(*g < x)
            p = g + 1;
        n = e - g - 1;
        e = c + n;
    }
    return NULL;
}
/**
size_t binplace(size_t n, double *c, double x)
{
    double *p, *e;
    for(p = c, e = p + n; p < e; ++p)
    {
        if(*p > x) return p - c;
    }
    return n;
}
*/

size_t binplace(size_t n, double *c, double x)
{
    double *p;
}

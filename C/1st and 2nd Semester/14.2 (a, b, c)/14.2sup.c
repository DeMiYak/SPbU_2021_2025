#include<stdio.h>
#include"head.h"
#include<math.h>

void assigndbl(size_t n, double *c, double *sum){
    double *p, *e;
    for(p = c, e = c + n; p < e; ++p){
        scanf("%lf", p);
        *sum += *p;
    }
}

void analysearray(size_t n, double *c, double *mar, double *msq, double *sum){
    printf("0");
}

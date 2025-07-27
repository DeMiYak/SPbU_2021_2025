#include<stdio.h>

void assigner(size_t n, double *c){
    for(size_t i = 0 ;i < n; ++i)
        scanf("%lf", &c[i]);
}

#include<stdio.h>
#include"head.h"


void assigndbl(size_t n, double *a){
    double *p, *e;
    for(p = a, e = p + n; p < e; ++p) scanf("%lf", p);
}

void assignint(size_t n, int *a){
    int *p, *e;
    for(p = a, e = p + n; p < e; ++p) scanf("%d", p);
}

size_t pickeven(size_t n, int *a){
    int *p, *e;
    size_t k = 0;
    for(p = a, e = a; p < a + n; ++p){
        if(*p % 2 == 0){
            *e = *p;
            e++;
            ++k;
        }
    }
    return k;
}

void printarint(size_t k, const int *a){
    const int *p;
    for(p = a; p < a + k; ++p) printf("%d\t", *p);
}

void printardbl(size_t k, const double *a){
    const double *p;
    for(p = a; p < a + k; ++p) printf("%lf\t", *p);
}

#include<stdio.h>
#include<math.h>
#include"integrals.h"

void assigner(size_t n, double *arr){
    //double *arr;
    //arr = malloc(sizeof(double) * n);
    for(size_t i=0;i<n;++i)
        scanf("%lf", &arr[i]);
    //return arr;
}


double avrectintegr(double l, double r, fnc_t pfnc, size_t n, double* c){
    double delta = (r - l)/n, value = 0;
    double s = l + delta/2;
    for(size_t i = 0; i < n; ++i){
        value += pfnc(s + delta*i, c);
    }
    return delta*value;
}


double iterintegr(qf_t pfnc, double eps, double l, double r, size_t n, fnc_t d, double *q, double* c){
    double k = pfnc(l, r, d, n, c);
    double z = pfnc(l, r, d, 2*n, c);
    while(fabs((z - k)/z) > eps){
        k = z;
        n *= 2;
        z = pfnc(l, r, d, 2*n, c);
    }
    *q = (z - k)/z;
    return z;
}

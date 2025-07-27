#include<stdio.h>


void arrayint(int x[], size_t n){
    for(size_t i = 0; i < n; i++) scanf("%d", &x[i]);
}



void arraydouble(double x[], size_t n){
    for(size_t i = 0; i < n; i++) scanf("%lf", &x[i]);
}

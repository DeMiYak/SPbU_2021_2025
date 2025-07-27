#include<stdio.h>

void arrayint(int x[], size_t n){
    for(size_t i = 0; i < n; i++) scanf("%d", &x[i]);
}


size_t arrayintcountk(const int x[], size_t n){
    size_t k = 0;
    for(size_t i = 1; i < n; i++){
        if((x[i-1] < 0 && x[i] > 0) || (x[i-1] > 0 && x[i] < 0)) ++k;
    }
    return k;
}

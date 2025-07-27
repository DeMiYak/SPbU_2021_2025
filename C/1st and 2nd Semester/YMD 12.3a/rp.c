#include<stdio.h>

void arrayint(int x[], size_t n){
    for(size_t i = 0; i < n; i++) scanf("%d", &x[i]);
}


size_t arrayintcountk(int x[], size_t n){
    size_t i, j = 0;
    for(i = 0; i < n; i++){
        if(x[i]%2 != 0){
            x[j] = x[i];
            ++j;
        }
    }
    for(size_t m = 0; m < j; ++m)
        printf("%d\t", x[m]);
    return j;
}

#include<stdio.h>

void arrayint(int x[], size_t n){
    for(size_t i = 0; i < n; i++) scanf("%d", &x[i]);
}


int arrayintcountk(const int x[], size_t n){
    int max1 = -1.0/0.0, max2 = -1.0/0.0;
    for(size_t i = 0; i < n; i++){
        if(x[i] >= max1){
            max2 = max1;
            max1 = x[i];
        } else if(x[i] < max1 && x[i] > max2) max2 = x[i];
    }
    if(max2 == -1.0/0.0){
        return -1;
    } else return max2;
}

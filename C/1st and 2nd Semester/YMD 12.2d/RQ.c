#include<stdio.h>

void arrayint(int x[], size_t n){
    for(size_t i = 0; i < n; i++) scanf("%d", &x[i]);
}


size_t arrayintcountk(const int x[], size_t n){
    size_t more = 1, less = 1, k = 1;
    for(size_t i = 1; i < n; i++){
        if(x[i] > x[i-1]){
            ++more;
            if(k < less) k = less;
            if(k < more) k = more;
            less = 1;
        } else if(x[i] < x[i-1]){
            ++less;
            if(k < less) k = less;
            if(k < more) k = more;
            more = 1;
        } else {
            ++less;
            ++more;
        }
        printf("i=%i less: %d more: %d\t\n", (int) i, less, more);
    }
    if(k < less) k = less;
    if(k < more) k = more;
    return k;
}

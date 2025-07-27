#include<stdio.h>
#include<limits.h>
#include"one.h"

int minarray(int a, int *k){
    int min = INT_MAX;
    int d;
    scanf("%d", &d);
    *k = 0;
    while(d != a){
        if(min > d) min = d;
        *k += 1;
        scanf("%d", &d);
    }
    return min;
}

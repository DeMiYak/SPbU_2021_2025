#include<stdio.h>

#define BUFFER_ARRAY 25

/**
* twodimarray создаёт двумерный массив
* размером n x m
*/
void twodimarray(double a[BUFFER_ARRAY][BUFFER_ARRAY], size_t n, size_t m){
    for(size_t i = 0; i < n; ++i){
        for(size_t j = 0; j < m; ++j){
            scanf("%lf", &a[i][j]);
            /**
            printf("\na = %lf i = %d j = %d", a[i][j], i, j);
            */
        }
    }
}

/**
* maxsumline находит строчку с максимальной суммой
* и выводит её индекс (начиная с 1)
*/
size_t maxsumline(double a[BUFFER_ARRAY][BUFFER_ARRAY], size_t n, size_t m){
    double s = -1.0/0.0;
    size_t ind = 0;

    for(size_t i = 0; i < n; ++i){
        double k = 0;
        for(size_t j = 0; j < m; ++j)
            k += a[i][j];
        if (k > s){ /*  */
            s = k;  /*  */
            ind = i;/*  */
        }
    }

    return ind;
}

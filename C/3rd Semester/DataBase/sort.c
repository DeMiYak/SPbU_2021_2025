#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "sort.h"

//sort function(select) n - size of array m - size of type
void sort_select(void *array, size_t n, size_t m, comp_func cmp){

    void *t = malloc(m);

    char *a = (char *) array;

    for(size_t i = 0, j; i < n - 1; ++i){

        size_t k = i;
        for(j = i + 1; j < n; ++j) if(cmp(a + k*m, array + j*m)) k = j;

        if(k != i){
            memcpy(t, a + k*m, m);
            memcpy(a + k*m, a + i*m, m);
            memcpy(a + i*m, t, m);
        }

    }

    free(t);
}

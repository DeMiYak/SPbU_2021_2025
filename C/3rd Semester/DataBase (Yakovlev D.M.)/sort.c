#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>
#include"sort.h"
#include"head24.h"

void swap_bases(base *a, base *b)
{
    base temp = *a;
    *a = *b;
    *b = temp;
}

//

size_t partition(base *d, size_t left, size_t right, cmpFunc cmp)
{
    size_t i = left, j = right;
    base a = d[(left + right)/2];
    while(i < j)
    {
        while(cmp(&d[i], &a) < 0) i++;
        while(cmp(&d[j], &a) > 0) j--;
        if(i < j)
        {
            swap_bases(&d[i], &d[j]);
            i++;
            j--;
        }
    }
    return cmp(&d[i], &a) >= 0 ? i: i + 1;
}

void quicksort(base *d, size_t left, size_t right, cmpFunc cmp)
{
    printf("\nleft = %Iu\nright = %Iu\n", left, right);
    if(left < right)
    {
        size_t q = partition(d, left, right, cmp);
        printf("\nq = %Iu\nd[%Iu] = %d", q, q, d[q].age);
        if(q)
        {
            quicksort(d, left, q-1, cmp);
            quicksort(d, q+1, right, cmp);
        }
    }
}

void data_sort_quick(base *d, size_t len, cmpFunc cmp)
{
    quicksort(d, 0, len - 1, cmp);
}

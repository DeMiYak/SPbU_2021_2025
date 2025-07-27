#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED

#include"head24.h"
typedef int (*cmpFunc)(const base *, const base *);

void swap_bases(base *a, base *b);

size_t partition(base *d, size_t left, size_t right, cmpFunc cmp);

void quicksort(base *d, size_t left, size_t right, cmpFunc cmp);

void data_sort_quick(base *d, size_t len, cmpFunc cmp);

#endif // SORT_H_INCLUDED

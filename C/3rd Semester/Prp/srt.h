#ifndef SRT_H_INCLUDED
#define SRT_H_INCLUDED

typedef int (*comp_func) (void *, void *);//compare function

void sort_select(void *array, size_t n, size_t m, comp_func cmp);//sort function(select sort)

#endif // SRT_H_INCLUDED

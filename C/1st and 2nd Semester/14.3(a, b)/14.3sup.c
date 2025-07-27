#include<stdio.h>
#include"head.h"
#include<stdlib.h>

void *BinSearch(void *arr, void *SearchElem, size_t sizeElem, size_t length, int (*compare)(const void *, const void *))
{
    /*
    size_t left = 0, right = length;
    while(right - left > 1)
    {
        size_t m = (left + right)/2;
        void *middle = arr + m*sizeElem;
        int result = compare(middle, SearchElem);
    */
    void *left = arr, *right = arr + length;
    while(right - left > 1)
    {
        void *middle = left + (right - left)/2;
        int result = compare(middle, SearchElem);
        switch(result)
        {
        case -1:
            left = middle;
            break;
        case 0:
            return middle;
            break;
        case 1:
            right = middle;
            break;
        default:
            break;
        }
        printf("%d")
    }
    if(compare(left, SearchElem) == 0) return left;
    return NULL;
}


void *BinPlace(void *arr, void *PlaceElem, size_t sizeElem, size_t length, int(*compare)(const void *, const void *))
{
    size_t left = 0, right = length;
    while(right - left > 1)
    {
        size_t m = (left + right)/2;
        void *middle = arr + m*sizeElem;
        int result = compare(middle, PlaceElem);
        if(result == 1)
            right = m;
        else left = m;
        // printf("\nleft = %Iu right = %Iu result = %d\n", left, right, result);
    }
    while(left < length && (compare(arr + left*sizeElem, PlaceElem)) < 1) {
        ++left;
        //printf("left = %Iu", left);
    }
    return arr + left*sizeElem;
}

void arrFill(int *arr, size_t length)
{
    int *arrEnd = arr + length;
    for(int *ptr = arr; ptr < arrEnd; ++ptr)
        scanf("%d", ptr);
}

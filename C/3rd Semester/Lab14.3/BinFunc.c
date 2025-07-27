//
// Created by vadim on 04.03.2022.
//

#include <stdio.h>
#include "BinFunc.h"

void *BinFind(void *array, void *n, size_t elSize, size_t len, int (*cmp)(const void *, const void *)) {
    size_t l = 0;
    size_t r = len;
    while (r - l > 1) {
        size_t m = (l + r) / 2;
        void *midEl = array + m * elSize;
        int res = cmp(midEl, n);
        switch (res) {
            case -1:
                l = m;
                break;
            case 0:
                return midEl;
            case 1:
                r = m;
                break;
            default:
                break;
        }
    }
    if (cmp(array + l * elSize, n) == 0)return array + l * elSize;
    return NULL;
}

void *UpperBound(void *array, void *n, size_t elSize, size_t len, int (*cmp)(const void *, const void *)) {
    size_t l = 0;
    size_t r = len;
    while (r - l > 1) {
        size_t m = (l + r) / 2;
        void *midEl = array + m * elSize;
        int res = cmp(midEl, n);
        if (res == 1) {
            r = m;
        } else {
            l = m;
        }
        //printf("l=%Iu r=%Iu\n", l, r);
    }
    while (l < len && (cmp(n, array + (l * elSize)) == 0)) {
        //printf("l=%Iu\n", l);
        l++;
    }
    return array + l * elSize;
}
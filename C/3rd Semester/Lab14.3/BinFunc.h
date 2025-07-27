//
// Created by vadim on 04.03.2022.
//

#ifndef LAB14_3_BINFUNC_H
#define LAB14_3_BINFUNC_H

void *BinFind(void *array, void *n, size_t elSize, size_t len, int (*cmp)(const void *, const void *));

void *UpperBound(void *array, void *n, size_t elSize, size_t len, int (*cmp)(const void *, const void *));

#endif //LAB14_3_BINFUNC_H

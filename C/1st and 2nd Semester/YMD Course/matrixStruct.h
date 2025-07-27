#ifndef MATRIXSTRUCT_H_INCLUDED
#define MATRIXSTRUCT_H_INCLUDED
#include<stddef.h>

//Line
typedef struct matrixLine
{
    size_t hor, vert;
    double *mat;
}matrixLine;

matrixLine *matrixLine_alloc(size_t i, size_t j);

matrixLine *matrixLine_clone(const matrixLine *m);

void matrixLine_free(matrixLine *m);

double *matrixLine_get(matrixLine *m, size_t i, size_t j);

const double *matrixLine_cget(matrixLine *m, size_t i, size_t j);

matrixLine *matrixLine_resize(matrixLine *m, size_t i, size_t j);

#endif // MATRIXSTRUCT_H_INCLUDED

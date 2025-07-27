#ifndef MATRIXINITFUNC_H_INCLUDED
#define MATRIXINITFUNC_H_INCLUDED

#include"matrixStruct.h"

//Line
matrixLine *matrixLine_set_zero(matrixLine *m);

matrixLine *matrixLine_identity(matrixLine *m);

matrixLine *matrixLine_assign(matrixLine *m, const matrixLine *m1);

void matrixLine_scan(matrixLine *m);

void matrixLine_copy(matrixLine *m, double *md, size_t n);

void matrixLine_print(matrixLine *m);

#endif // MATRIXINITFUNC_H_INCLUDED

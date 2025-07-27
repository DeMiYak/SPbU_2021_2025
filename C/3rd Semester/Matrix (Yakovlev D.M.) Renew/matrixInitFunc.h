#ifndef MATRIXINITFUNC_H_INCLUDED
#define MATRIXINITFUNC_H_INCLUDED

#include"matrixStruct.h"
//Dyn
/*
matrixDyn *matrixDyn_set_zero(matrixDyn *m);

matrixDyn *matrixDyn_identity(matrixDyn *m);

matrixDyn *matrixDyn_assign(matrixDyn *m, const matrixDyn *m1);

void matrixDyn_scan(matrixDyn *m);

void matrixDyn_print(matrixDyn *m);

*/
//Line
matrixLine *matrixLine_set_zero(matrixLine *m);

matrixLine *matrixLine_identity(matrixLine *m);

matrixLine *matrixLine_assign(matrixLine *m, const matrixLine *m1);

void matrixLine_scan(matrixLine *m);

void matrixLine_print(matrixLine *m);

#endif // MATRIXINITFUNC_H_INCLUDED

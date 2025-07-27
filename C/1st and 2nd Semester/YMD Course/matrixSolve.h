#ifndef MATRIXSOLVE_H_INCLUDED
#define MATRIXSOLVE_H_INCLUDED

#include"matrixStruct.h"

//Line
matrixLine * matrixLine_Gauss_Method(matrixLine *m, matrixLine *ext);

double matrixLine_Norm(matrixLine *m);

matrixLine * matrixLine_Taylor_Exp(const matrixLine *m, double eps);

#endif // MATRIXSOLVE_H_INCLUDED

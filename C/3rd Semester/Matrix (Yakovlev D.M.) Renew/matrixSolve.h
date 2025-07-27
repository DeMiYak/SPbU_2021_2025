#ifndef MATRIXSOLVE_H_INCLUDED
#define MATRIXSOLVE_H_INCLUDED

//Dyn
/*
matrixDyn * matrixDyn_Gauss_Method(matrixDyn *m, matrixDyn *ext);

double matrixDyn_Norm(matrixDyn *m);

matrixDyn * matrixDyn_Taylor_Exp(const matrixDyn *m, double eps);
*/
//Line
matrixLine * matrixLine_Gauss_Method(matrixLine *m, matrixLine *ext);

double matrixLine_Norm(matrixLine *m);

matrixLine * matrixLine_Taylor_Exp(const matrixLine *m, double eps);

#endif // MATRIXSOLVE_H_INCLUDED

#ifndef PP_H_INCLUDED
#define PP_H_INCLUDED

void setarray(double* c);

double assigner(double x, double* a);

double avrectintegr(double a, double b, double (*pfnc)(double x, double* c), size_t n, double* c);

double parabintegr(double a, double b, double (*pfnc)(double x, double* c), size_t n, double* c);

#endif // PP_H_INCLUDED

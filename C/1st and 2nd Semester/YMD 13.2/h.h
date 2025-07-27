#ifndef H_H_INCLUDED
#define H_H_INCLUDED

void setarray(double* c);

double assigner(double x, double* a);

typedef double (*fnc_t)(double x, double* c);

double avrectintegr(double a, double b, fnc_t pfnc, size_t n, double* c);

typedef double (*qf_t)(double, double, fnc_t, size_t, double*);

double iterintegr(qf_t pfnc, double eps, double a, double b, size_t n, fnc_t d, double *q, double* c);

#endif // H_H_INCLUDED

#ifndef INTEGRALS_H_INCLUDED
#define INTEGRALS_H_INCLUDED
#define e 2.71828182845904523536
#define M_PI 3.14159265358979323846

void assigner(size_t n, double* arr);

typedef double (*fnc_t)(double x, double* c);

double avrectintegr(double a, double b, fnc_t pfnc, size_t n, double* c);

typedef double (*qf_t)(double, double, fnc_t, size_t, double*);

double iterintegr(qf_t pfnc, double eps, double a, double b, size_t n, fnc_t d, double *q, double* c);

#endif // INTEGRALS_H_INCLUDED

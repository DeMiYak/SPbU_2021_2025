#ifndef TASK1_H_INCLUDED
#define TASK1_H_INCLUDED

#include<iostream>
#include<math.h>

double f(double x);

double df(double x);

double ddf(double x);

double fi(double x);

double dfi(double x);

double secf(double x, double y);

void BiSect(double beg, double end, double h, double eps, double (*f)(double));

void NewtonApprox(double beg, double end, double h, double eps, double (*f)(double), double(*fi)(double));

void ModNewtonApprox(double beg, double end, double h, double eps, double (*f)(double), double(*df)(double));

void SecantApprox(double beg, double end, double h, double eps, double (*f)(double), double(*secf)(double, double));
#endif // TASK1_H_INCLUDED

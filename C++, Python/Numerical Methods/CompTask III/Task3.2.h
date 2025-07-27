#ifndef TASK3_2_H_INCLUDED
#define TASK3_2_H_INCLUDED

#include<locale.h>
#include<iostream>
#include<math.h>
#include<iomanip>
using namespace std;

double f2(double x);

double* buildup(double(*f)(double), size_t size, double a, double *h);

double* firstDer(double(*f)(double), double const* arg, size_t size, double h);

double* secondDer(double(*f)(double), double const* arg, size_t size, double h);

void introTwo();

void procedureThree();
#endif // TASK3_2_H_INCLUDED

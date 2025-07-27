#ifndef TASK1_H
#define TASK1_H

#include<cmath>

//
const double EPSILON = 1e-5;
const double X_LEFT_ROOT = (1 + sqrt(21)) / 2 + EPSILON;
const double X_RIGHT_ROOT = (1 - sqrt(21)) / 2 - EPSILON;
// comment 

double f_1(double x) {
	double temp;
	if (x > X_LEFT_ROOT || x < X_RIGHT_ROOT) return x * x;
	else return (temp = sin(x), temp*temp); // comment
}

double f_2(double x) {
	double temp;
	return (x > X_LEFT_ROOT || x < X_RIGHT_ROOT) ? x * x : (temp = sin(x), temp*temp); // comment
}

#endif

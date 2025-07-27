#include "OptimalParameterMethod.h"

void OptimalParameterMethod::Calculate(const RESOLVER& resolver)
{
	const double hx_2 = pow(resolver.GetHX(), -2), hy_2 = pow(resolver.GetHY(), -2);
	opt_par = 1 / (2 * (hx_2 + hy_2));
	resU = resolver.GetU();
	for (sizetype i = 0; i < iter_num; ++i) {
		IterateOnce(resolver);
	}
}

void OptimalParameterMethod::ChangeIterNum(sizetype _iter_num)
{
	iter_num = _iter_num;
}

void OptimalParameterMethod::PrintName()
{
	cout << endl << "Optimal Parameter Method. Variant 4" << endl;
}

void OptimalParameterMethod::IterateOnce(const RESOLVER& resolver)
{
	// Приращения в степени -2
	const double hx_2 = pow(resolver.GetHX(), -2), hy_2 = pow(resolver.GetHY(), -2);
	const double opt_temp = opt_par;
	const sizetype Nx = resolver.GetNX(), My = resolver.GetMY();
	// Предыдущая итерация (из U_k в U_{k+1})
	prevResU = resU;
	for (sizetype i = 1; i < Nx; ++i) {
		for (sizetype j = 1; j < My; ++j) {
			resU[i][j] = prevResU[i][j] + opt_temp*(hx_2*(prevResU[i+1][j] + 
				prevResU[i-1][j] - 2*prevResU[i][j]) + 
				hy_2*(prevResU[i][j-1] + prevResU[i][j+1] - 2*prevResU[i][j]));
		}
	}
}

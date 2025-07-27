#include "SeidelMethod.h"

void SeidelMethod::Calculate(const RESOLVER& resolver)
{
	resU = resolver.GetU();
	for (sizetype i = 0; i < iter_num; ++i) {
		IterateOnce(resolver);
	}
}

void SeidelMethod::ChangeIterNum(sizetype _iter_num)
{
	iter_num = _iter_num;
}

void SeidelMethod::PrintName()
{
	cout << endl << "Seidel Method. Variant 4" << endl;
}

void SeidelMethod::IterateOnce(const RESOLVER& resolver)
{
	// Приращения в степени -2
	const double hx_2 = pow(resolver.GetHX(), -2), hy_2 = pow(resolver.GetHY(), -2);
	const double sp_cf = 1 / (2 * (hx_2 + hy_2));
	const sizetype Nx = resolver.GetNX(), My = resolver.GetMY();
	// Предыдущая итерация (из U_k в U_{k+1})
	prevResU = resU;
	for (sizetype i = 1; i < Nx; ++i) {
		for (sizetype j = 1; j < My; ++j) {
			resU[i][j] = sp_cf * ((prevResU[i + 1][j] + resU[i - 1][j]) * hx_2
				+ (resU[i][j - 1] + prevResU[i][j + 1]) * hy_2);
		}
	}
}

#include "OverRelaxationMethod.h"

void OverRelaxationMethod::Calculate(const RESOLVER& resolver)
{
	resU = resolver.GetU();
	for (sizetype i = 0; i < iter_num; ++i) {
		IterateOnce(resolver);
	}
}

void OverRelaxationMethod::ChangeIterNum(sizetype _iter_num)
{
	iter_num = _iter_num;
}

void OverRelaxationMethod::PrintName()
{
	cout << endl << "Over-Relaxation Method. Variant 4" << endl;
}

void OverRelaxationMethod::ChangeOmega(double _omega)
{
	if (_omega >= 2 || _omega <= 0) return;
	omega = _omega;
}

void OverRelaxationMethod::IterateOnce(const RESOLVER& resolver)
{
	// Приращения в степени -2
	const double hx_2 = pow(resolver.GetHX(), -2), hy_2 = pow(resolver.GetHY(), -2);
	const double sp_cf = 1 / (2 * (hx_2 + hy_2));
	const sizetype Nx = resolver.GetNX(), My = resolver.GetMY();
	// Предыдущая итерация (из U_k в U_{k+1})
	prevResU = resU;
	for (sizetype i = 1; i < Nx; ++i) {
		for (sizetype j = 1; j < My; ++j) {
			resU[i][j] = prevResU[i][j] 
				+ omega * sp_cf * ((prevResU[i + 1][j] 
				+ resU[i - 1][j] 
				- 2*prevResU[i][j]) * hx_2
				+ (resU[i][j - 1] 
				+ prevResU[i][j + 1]
				- 2*prevResU[i][j]) * hy_2);
		}
	}
}

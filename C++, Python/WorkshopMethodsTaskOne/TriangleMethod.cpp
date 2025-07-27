#include "TriangleMethod.h"

void TriangleMethod::Calculate(const RESOLVER& resolver)
{
	// Вычисление параметров омеги и тау
	const double hx_2 = pow(resolver.GetHX(), -2), hy_2 = pow(resolver.GetHY(), -2);
	const double pi_x = M_PI_2 * resolver.GetHX() / resolver.GetLX();
	const double pi_y = M_PI_2 * resolver.GetHY() / resolver.GetLY();
	const double cos_x = cos(pi_x), sin_x = sin(pi_x);
	const double cos_y = cos(pi_y), sin_y = sin(pi_y);
	const double delta_small = 4 * (hx_2 * sin_x * sin_x + hy_2 * sin_y * sin_y);
	const double delta_big = 4 * (hx_2 * cos_x * cos_x + hy_2 * cos_y * cos_y);
	// Параметр омега
	omega = 2 / sqrt(delta_small * delta_big);
	const double nu = delta_small / delta_big;
	const double gamma_1 = delta_small / (2 + 2 * sqrt(nu));
	const double gamma_2 = delta_small / (4 * sqrt(nu));
	// Параметр тау
	tau = 2 / (gamma_1 + gamma_2);
	resU = resolver.GetU();
	for (sizetype i = 0; i < iter_num; ++i) {
		IterateOnce(resolver);
	}
}

void TriangleMethod::ChangeIterNum(sizetype _iter_num)
{
	iter_num = _iter_num;
}

void TriangleMethod::PrintName()
{
	cout << endl << "Triangle Method. Variant 4" << endl;
}

void TriangleMethod::ChangeOmega(double _omega)
{
	if (_omega >= 2 || _omega <= 0) return;
	omega = _omega;
}

void TriangleMethod::ChangeTau(double _tau)
{
	tau = _tau;
}

void TriangleMethod::IterateOnce(const RESOLVER& resolver)
{
	/// Посмотрим на алгоритм, изложенный для  
	/// попеременно-треугольного метода.
	/// Начнём с основ, что пригодится:
	/// Временная матрица с нулевыми границами
	const sizetype Nx = resolver.GetNX(), My = resolver.GetMY();
	vector<vector<double>> tempOmega(Nx+1, vector<double>(My+1, 0));
	/// Далее, необходим вектор tempPhi, значения для которого
	/// будут результатом простой итерации
	vector<vector<double>> tempPhi(Nx+1, vector<double>(My+1, 0));

	// Приращения в степени -2
	const double hx_2 = pow(resolver.GetHX(), -2), hy_2 = pow(resolver.GetHY(), -2);
	//const double sp_cf = 1 / (2 * (hx_2 + hy_2));
	
	// Предыдущая итерация (из U_k в U_{k+1})
	prevResU = resU;
	// В этом цикле вычисляем tempPhi
	for (sizetype i = 1; i < Nx; ++i) {
		for (sizetype j = 1; j < My; ++j) {
			tempPhi[i][j] = 
				(prevResU[i + 1][j] + prevResU[i - 1][j] - 2*prevResU[i][j]) * hx_2
				+ 
				(prevResU[i][j - 1] + prevResU[i][j + 1] - 2*prevResU[i][j]) * hy_2;
		}
	}
	// Далее хотим вычислить tempOmega
	// Используется омега
	const double k_x = omega * hx_2, k_y = omega * hy_2;
	const double k_denom = 1 + k_x + k_y;
	for (sizetype i = 1; i < Nx; ++i) {
		for (sizetype j = 1; j < My; ++j) {
			tempOmega[i][j] = 
				(tempPhi[i][j] 
				+ k_x * tempOmega[i-1][j]
				+ k_y * tempOmega[i][j-1]) / k_denom;
		}
	}
	// А теперь хотим вычислить итоговый Omega-вектор
	vector<vector<double>> resultOmega(Nx + 1, vector<double>(My + 1, 0));
	for (sizetype i = Nx-1; i > 0; --i) {
		for (sizetype j = My-1; j > 0; --j) {
			resultOmega[i][j] =
				(k_x * resultOmega[i+1][j]
				+ k_y * resultOmega[i][j+1]
				+ tempOmega[i][j]) / k_denom;
		}
	}

	// Вычисление новой итерации с параметром тау
	for (sizetype i = 1; i < Nx; ++i) {
		for (sizetype j = 1; j < My; ++j) {
			resU[i][j] = prevResU[i][j] + tau*resultOmega[i][j];
		}
	}
}

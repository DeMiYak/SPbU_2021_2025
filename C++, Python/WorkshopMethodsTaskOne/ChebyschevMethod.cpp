#include"ChebyschevMethod.h"

//void ChebyschevMethod::Re_Calculate(sizetype iter_num, const RESOLVER& resolver)
//{
//}

void ChebyschevMethod::Calculate(const RESOLVER& resolver)
{
	const double hx_2 = pow(resolver.GetHX(), -2), hy_2 = pow(resolver.GetHY(), -2);
	const double cos_x = cos(M_PI * resolver.GetHX() / resolver.GetLX());
	const double cos_y = cos(M_PI * resolver.GetHY() / resolver.GetLY());
	const double cos_main = cos_x * hx_2 + cos_y * hy_2;
	resU = resolver.GetU();
	
	// Находим наименьшую степень двойки, превосходящую iter_num
	//int twoDegree = ceil(log2(iter_num));
	//vector<double> chParam = FindChebyshevSequence(twoDegree);
	for (int i = 1; i <= iter_num; ++i) {
		double csa = cos(M_PI_2 * (2*i-1) / iter_num);
		double seg = 2. * (hx_2 + hy_2 - cos_main*csa);
		sp_par = 1. / seg;
		IterateOnce(resolver);
	}
}

void ChebyschevMethod::ChangeIterNum(sizetype _iter_num)
{
	iter_num = _iter_num;
}

void ChebyschevMethod::PrintName()
{
	cout << endl << "Chebyschev Method. Variant 4" << endl;
}

void ChebyschevMethod::IterateOnce(const RESOLVER& resolver)
{
	// Приращения в степени -2
	const double hx_2 = pow(resolver.GetHX(), -2), hy_2 = pow(resolver.GetHY(), -2);
	const sizetype Nx = resolver.GetNX(), My = resolver.GetMY();
	// Предыдущая итерация (из U_k в U_{k+1})
	prevResU = resU;
	for (sizetype i = 1; i < Nx; ++i) {
		for (sizetype j = 1; j < My; ++j) {
			resU[i][j] = prevResU[i][j] + sp_par * (hx_2 * (prevResU[i + 1][j] +
				prevResU[i - 1][j] - 2 * prevResU[i][j]) +
				hy_2 * (prevResU[i][j - 1] + prevResU[i][j + 1] - 2 * prevResU[i][j]));
		}
	}
}

//vector<double> ChebyschevMethod::FindChebyshevSequence(int two_degree)
//{
//	if (two_degree == 0) return vector<double>(2, 1);
//	const double length = pow(2, two_degree);
//	vector<vector<double>> Count_Vector(two_degree, vector<double>(length+1, 1));
//	Count_Vector[0][2] = 3;
//	for (int i = 1; i < two_degree; ++i) {
//		int temp = pow(2, i + 1);
//		int doub_temp = temp * 2;
//		for (int j = 2; j <= temp; ++j) {
//			if (j % 2 == 0) {
//				Count_Vector[i][j] = doub_temp - Count_Vector[i][j - 1];
//			}
//			else {
//				Count_Vector[i][j] = Count_Vector[i - 1][(j + 1)/2];
//			}
//		}
//	}
//	return Count_Vector[two_degree-1];
//}

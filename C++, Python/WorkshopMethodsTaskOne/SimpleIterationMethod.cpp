#include "SimpleIterationMethod.h"

// ������������ U (U_0) � resU �������� ������ ��������
// � ��������-����������� resU

void SimpleIterationMethod::Calculate(const RESOLVER& resolver)
{
	resU = resolver.GetU();
	for (sizetype i = 0; i < iter_num; ++i) {
		IterateOnce(resolver);
	}
}

// ��������: � ���������� ����� �������� ���������� �������� Calculate,
// ����� �� ���������� ������
void SimpleIterationMethod::ChangeIterNum(sizetype _iter_num)
{
	// ����� ����� ���-�� ������� �������� � �����������
	iter_num = _iter_num;
}

/// <summary>
/// ������ ������, ����� �������� ����� ��������
/// </summary>
/// <param name="_iter_num"></param>
/// <param name="resolver"></param>

//void SimpleIterationMethod::Re_Calculate(sizetype _iter_num, const RESOLVER& resolver)
//{
//	if (iter_num == _iter_num) return;
//	else if (iter_num < _iter_num) {
//		for (sizetype i = iter_num; i < _iter_num; ++i) {
//			IterateOnce(resolver);
//		}
//		iter_num = _iter_num;
//	}
//	else {
//		iter_num = _iter_num;
//		Calculate(resolver);
//	}
//}

//void SimpleIterationMethod::PrintData()
//{
//	sizetype Nx = resU.size(), My = resU[0].size();
//	cout << endl << "Number of iterations: " << iter_num << endl;
//	for (int i = My-1; i >= 0; --i) {
//		for (int j = 0; j < Nx; ++j) {
//			cout << resU[j][i] << setw(7);
//		}
//		cout << endl;
//	}
//	cout << endl;
//}

void SimpleIterationMethod::PrintName()
{
	cout << endl << "Simple Iteration Method. Variant 4." << endl;
}

/// <summary>
/// �������� �������� ��� ������ ������� ��������
/// </summary>
/// <param name="resolver"></param>
void SimpleIterationMethod::IterateOnce(const RESOLVER& resolver)
{	
	// ���������� � ������� -2
	const double hx_2 = pow(resolver.GetHX(), -2), hy_2 = pow(resolver.GetHY(), -2);
	const double sp_cf = 1 / (2*(hx_2 + hy_2));
	const sizetype Nx = resolver.GetNX(), My = resolver.GetMY();
	// ���������� �������� (�� U_k � U_{k+1})
	
	/*const vector<vector<double>> tempU = resU;
	for (sizetype i = 1; i < Nx; ++i) {
		for (sizetype j = 1; j < My; ++j) {
			resU[i][j] = sp_cf*( (tempU[i+1][j] + tempU[i-1][j])*hx_2 
				+ (tempU[i][j-1] + tempU[i][j+1])*hy_2);
		}
	}*/

    prevResU = resU;
	for (sizetype i = 1; i < Nx; ++i) {
		for (sizetype j = 1; j < My; ++j) {
			resU[i][j] = sp_cf * ((prevResU[i + 1][j] + prevResU[i - 1][j]) * hx_2
				+ (prevResU[i][j - 1] + prevResU[i][j + 1]) * hy_2);
		}
	}
}

/// ��������, � ���������� ����� ��������� U_k, �� ����� ��������
/// �������� ������ ������. ����: ����� ���������� ���������� 
/// U_k � ������������ ���������, ����� ���� � ���.���������� �����
/// ��������������
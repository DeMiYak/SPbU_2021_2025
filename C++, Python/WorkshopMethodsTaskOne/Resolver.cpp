#include "Resolver.h"

double solution(double x, double y) {
	return exp(x) * sin(y);
}

double solPolynomial(double x, double y) {
	return x * x - x * y + y * y;
}

void RESOLVER::ChangeSegmentAmount(sizetype _Nx, sizetype _My)
{
	if (_Nx == Nx && _My == My) return;
	Nx = _Nx;
	My = _My;
	hx = lx / Nx;
	hy = ly / My;
	InitU();
}

void RESOLVER::ConfigL(double _lx, double _ly)
{
	lx = _lx;
	ly = _ly;
	hx = lx / Nx;
	hy = ly / My;
	InitU();
	// ���-�� ��� ����������� ����� �������
}

void RESOLVER::PrintData()
{
	cout << "Resolver Data:" << endl;
	cout << "Lx = " << lx << "\tLy = " << ly << endl;
	cout << "Nx = " << Nx << "\tMy = " << My << endl;
	cout << "hx = " << hx << "\thy = " << hy << endl;
	cout << endl << "Nodes Data: " << endl;
	cout << fixed;
	for (int i = My; i >= 0; --i) {
		for (int j = 0; j <= Nx; ++j) {
			cout << U[j][i] << setw(7);
		}
		cout << endl;
	}
	cout << endl;
}

/// <summary>
/// ������������� ���������� ������� ������,
/// ����� ��������������� ��� �������, ��� � �������
/// </summary>
void RESOLVER::InitU()
{
	double xTemp = 0, yTemp = hy;
	/// ������������� � ����������� ��������� ��������
	if (U.size() != Nx + 1 || U[0].size() != My + 1) {
		U.resize(Nx + 1, vector<double>(My + 1, 0));
	}
	
	// ������� �� ��������, ������������ ��� X, � ����� Y
	for (size_t i = 0; i <= Nx; ++i) {
		U[i][0] = solptr(xTemp, 0);
		U[i][My] = solptr(xTemp, ly);
		xTemp += hx;
	}

	for (size_t i = 1; i < My; ++i) {
		U[0][i] = solptr(0, yTemp);
		U[Nx][i] = solptr(lx, yTemp);
		yTemp += hy;
	}
}
void RESOLVER::PickSolution(SOLUTION SOL)
{
	switch (SOL)
	{
	case SOL_0:
		solptr = solution;
		break;
	case SOL_1:
		solptr = solPolynomial;
		break;
	}

}

/// ������� ������� ���������, ��� ��������� �� �������?
/// �������� ������� - ��� ������������� ��������

/// ���� �� ����: � �������� U ����������� ����������� ������� � ��������,
/// ����� ����� ������������ �������� �� ������� ��� ����������, ������
/// ����, ����� ������ ��� ��������� �������� �� �����

/// ������ ����� ��������� ��, ��� ������ �������� �� ��� ������
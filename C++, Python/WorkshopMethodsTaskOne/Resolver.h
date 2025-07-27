#pragma once
#define _USE_MATH_DEFINES
#include<iostream>
#include<math.h>
#include<vector>
#include<iomanip>
#include"Norm.h"

using namespace std;

// ������� �4
enum SOLUTION{SOL_0, SOL_1};
enum METHOD{SIM, SEIMET, CHEBY, CHEBYTRI, TRI, OPTPAR, OVERREL};
typedef size_t sizetype;
typedef double(*funptr) (double, double);



/// <summary>
/// ��������� - �����, ���������� ������� � ��������
/// � ���������� �������� �� �����
/// </summary>
class RESOLVER {
public:
	RESOLVER(double _lx = 1,
		double _ly = M_PI,
		sizetype _Nx = 30,
		sizetype _My = 20,
		SOLUTION _SOL = SOL_0) {
		lx = _lx; 
		ly = _ly;
		Nx = _Nx;
		My = _My;
		hx = _lx / _Nx;
		hy = _ly / _My;
		PickSolution(_SOL);
		InitU();
	}
	double GetLX() const { return lx; }
	double GetLY() const { return ly; }
	double GetHX() const { return hx; }
	double GetHY() const { return hy; }
	sizetype GetNX() const { return Nx; }
	sizetype GetMY() const { return My; }
	funptr GetSolPtr() const { return solptr; }
	vector<vector<double>> GetU() const { return U; }
	void ChangeSegmentAmount(sizetype _Nx, sizetype _My);
	void ConfigL(double _lx, double _ly);
	void PrintData();
private:
	/// <summary>
	/// ������������� ������� U
	/// </summary>
	void InitU();
	/// <summary>
	/// ����� �������
	/// </summary>
	/// <param name="SOL"></param>
	void PickSolution(SOLUTION SOL);
	// ����� ��������������
	double lx, ly;
	// ���������� ����� ����������
	double hx, hy;
	// ����� ��������� �� ����
	sizetype Nx, My;
	
	// ��� ������� (������ �������� �������� �������� ������)
	/*SOLUTION SOL;*/
	
	/// <summary>
	/// ��������� �� ��� ������� � ������, ���� ��������� ����� ���������
	/// �������. ������ ������������ ������ �������� �������� ������.
	/// </summary>
	funptr solptr;
	
	/// <summary>
	/// ������ �������� ������� u � �����.
	/// </summary>
	vector<vector<double>> U;
};
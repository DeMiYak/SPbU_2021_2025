#pragma once
#include"Resolver.h"
#include<iostream>

/// <summary>
/// "������ ��� �������", ��� ����������:
/// 1. ����������� ����� ��� ���������� (Calculate)
/// 2. ��������, ����� ���������� ���������� (PrintData)
/// 3. ����� RESOLVER ��� ���������� ����������
/// 4. ���� ���� sizetype (size_t) ��� ����������� ��������,
/// ������, ��� ��������� ����� �������� ���������� �������������
/// ���������� (����� ������� �� �������, ���� ����� �������� ������, ��
/// ������ �������������� ��� ��������� ���, � ���� ������, �� ��� �����)
/// 5. ���� ���� double ��� ����������� �������� (������� ��������� ������
/// ��������) 
/// </summary>
class BaseMethodGenerator {
public:
	BaseMethodGenerator(sizetype _iter_num) { iter_num = _iter_num; }
	virtual void Calculate(const RESOLVER& resolver) = 0;
	virtual void ChangeIterNum(sizetype _iter_num) = 0;
	virtual void Re_Calculate(sizetype _iter_num, const RESOLVER& resolver);
	virtual void PrintData();
	virtual vector<vector<double>> GetResU() const { return resU; }
	virtual vector<vector<double>> GetPrevResU() const { return prevResU; }
	virtual sizetype GetIterNum() const { return iter_num; }
	virtual void PrintName() = 0;
protected:
	// ����� resU, iter_num, ����� ��������� U_k,
	// ���������� �������. ����� �������, ����� � ����������
	// ������ ��������� U_0. �� ����, ��������� - ������
	// ��� ���������� ��������
	/// <summary>
	/// �����, ����������� U
	/// </summary>
	vector<vector<double>> resU;
	vector<vector<double>> prevResU;
	/// <summary>
	/// ����� ��������
	/// </summary>
	sizetype iter_num;
	virtual void IterateOnce(const RESOLVER& resolver) = 0;
};
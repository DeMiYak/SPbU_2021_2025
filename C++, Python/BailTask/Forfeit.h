#pragma warning(disable:4996)
#include<random>


/// � ����� ��������� ������������ �����
/// ���� double � �������� ���� (����������� ��������)
/// ����� �������� ������� � �������������� �. ������� ������ ������ ���������
/// Ÿ ��������� - ���� � ��� ��������� �� �������.
/// ������ ��������� �� �. - �� ������ ������� ������ � ����� ����� (������, ���� ����� �������)
/// ������ ��������� �� �. - ��� ������ � ���� ������.
/// 
/// ����� ������ ����� ����� � �����, �� �������� ���� � ������,
/// � �������� ���� ����� � �����

/// ���������� � ���� ������������ �����
void CreateFile(const char* fileName, int dataCount, double* array);

void ReadFile(const char* fileName, int dataCount, double* array);
/// �������� ����� � �����
/// �� ��������
bool ChangeByCriteria(FILE* file, bool (*cmpFunc)(const double& num), void(*cngFunc)(double& num));

bool GTZero(const double& num);
bool LTZero(const double& num);

void MakeSquare(double& num);
void ChangeSign(double& num);
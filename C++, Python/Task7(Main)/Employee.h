#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>

const int NSYMB = 15;
const int NEMPL = 100;
const int NPERS = 15;

struct EMPLOYEE {
	char surname[NSYMB];
	char position[NSYMB];
	int salary;
};

struct PERSONNEL {
	int NumDept;
	EMPLOYEE EmpList[NEMPL];
};

// ���� �� ����� ���������������� ������ �� 2) ��������
void From_File(const char* fname, PERSONNEL* l, int* pn);

// ����� � ���� ���������������� ������ �� 2) ��������
void In_File(const char* fname, PERSONNEL* l, int n);

// ������� �������������� �� ������ ������ � �� �������
// ������������ ������� ���������� �� ���. �������� � �������������� ���������
// �� ������� ���������
void Double_Sort(PERSONNEL** pl, int n, int(*comparePer)(const void*, const void*), int(*compareEmp)(const void*, const void*));

//void Sort(EMPLOYEE** pemp, int(*compareEmp)(const void*, const void*));
// ������� ��������� �� ������ ������
int cmp_NumDept(const void* pOne, const void* pTwo);

// ������� ��������� �� ������� ����������
int cmp_Surname(const void* pOne, const void* pTwo);

// ����� �� ������ ������, ���� ���������������� �����
PERSONNEL* Search_By_Dept(const PERSONNEL* dept, PERSONNEL** l, int n, int(*comparePer)(const void*, const void*));

// ���������� �������� �� ����������

// ����� �� ����� �������������� ������
//void Sorted_Print(PERSONNEL** pl, int n, int(*comparePer)(const void*, const void*), int(*compareEmp)(const void*, const void*));

// ����� ���� ������� �� ����� �������
void Print(PERSONNEL** l, int n);

// ����� ������ ������
void Print_Dept(const PERSONNEL& l);

// ����� �����
void Print_Employee(const EMPLOYEE& emp);
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

// Ввод из файла неупорядоченного списка из 2) структур
void From_File(const char* fname, PERSONNEL* l, int* pn);

// Вывод в файл неупорядоченного списка из 2) структур
void In_File(const char* fname, PERSONNEL* l, int n);

// Двойное упорядочивание по номеру отдела и по фамилии
// Библиотечная функция сортировки по зад. критерию с использованием указателя
// на функцию сравнения
void Double_Sort(PERSONNEL** pl, int n, int(*comparePer)(const void*, const void*), int(*compareEmp)(const void*, const void*));

//void Sort(EMPLOYEE** pemp, int(*compareEmp)(const void*, const void*));
// Функция сравнения по номеру отдела
int cmp_NumDept(const void* pOne, const void* pTwo);

// Функция сравнения по фамилии сотрудника
int cmp_Surname(const void* pOne, const void* pTwo);

// Поиск по номеру отдела, свой последовательный поиск
PERSONNEL* Search_By_Dept(const PERSONNEL* dept, PERSONNEL** l, int n, int(*comparePer)(const void*, const void*));

// Сортировка структур по указателям

// Вывод на экран упорядоченного списка
//void Sorted_Print(PERSONNEL** pl, int n, int(*comparePer)(const void*, const void*), int(*compareEmp)(const void*, const void*));

// Вывод всех отделов со всеми кадрами
void Print(PERSONNEL** l, int n);

// Вывод одного отдела
void Print_Dept(const PERSONNEL& l);

// Вывод кадра
void Print_Employee(const EMPLOYEE& emp);
#pragma warning(disable:4996)
#include<random>


/// В файле находятся вещественные числа
/// типа double в бинарном виде (реализовать функцией)
/// Нужно написать функцию и протестировать её. Функция должна делать следующее
/// Её параметры - файл и два указателя на функции.
/// Первый указатель на ф. - по какому условию искать в файле число (первое, удов этому условию)
/// Второй указатель на ф. - что делать с этим числом.
/// 
/// Нужно искать число прямо в файле, не считывая файл в памяти,
/// и заменять тоже прямо в файле

/// Записывает в файл вещественные числа
void CreateFile(const char* fileName, int dataCount, double* array);

void ReadFile(const char* fileName, int dataCount, double* array);
/// Изменяет число в файле
/// по критерию
bool ChangeByCriteria(FILE* file, bool (*cmpFunc)(const double& num), void(*cngFunc)(double& num));

bool GTZero(const double& num);
bool LTZero(const double& num);

void MakeSquare(double& num);
void ChangeSign(double& num);
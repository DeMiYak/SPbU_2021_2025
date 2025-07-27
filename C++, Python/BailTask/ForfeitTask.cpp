// BailTask.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include<iostream>
#include"Forfeit.h"
/// В файле находятся вещественные числа
/// типа double в бинарном виде (реализовать функцией)
/// Нужно написать функцию и протестировать её. Функция должна делать следующее
/// Её параметры - файл и два указателя на функции.
/// Первый указатель на ф. - по какому условию искать в файле число (первое, удов этому условию)
/// Второй указатель на ф. - что делать с этим числом.
/// 
/// Нужно искать число прямо в файле, не считывая файл в памяти,
/// и заменять тоже прямо в файле
bool hasNegative(double* array, const int dataCount) {
	for (int i = 0; i < dataCount; ++i)
		if (array[i] < 0) return true;
	return false;
}

int main() {
	const char* dbOne = "DoubleBinaryOne";
	const int dataCount = 8;
	double array[] = {-1,2,-3,4,-5,6,-7,8};
	CreateFile(dbOne, dataCount, array);
	
	// Test 1
	std::cout << "Test 1" << std::endl;
	for (int i = 0; i < dataCount; std::cout << array[i++] << " ");
	std::cout << std::endl;
	FILE* file = fopen(dbOne, "rb+");
	ChangeByCriteria(file, GTZero, MakeSquare);
	fclose(file);
	ReadFile(dbOne, dataCount, array);
	for (int i = 0; i < dataCount; std::cout << array[i++] << " ");
	std::cout << std::endl;

	// Test 2
	std::cout << "Test 2" << std::endl;
	while (hasNegative(array, dataCount)) {
		file = fopen(dbOne, "rb+");
		ChangeByCriteria(file, LTZero, MakeSquare);
		fclose(file);
		ReadFile(dbOne, dataCount, array);
		for (int i = 0; i < dataCount; std::cout << array[i++] << " ");
		std::cout << std::endl;
	}

	const char* dbTwo = "DoubleBinaryTwo";
	const int dataCountTwo = 6;
	double arrayTwo[] = {-1,-3,0,-7,3,1};
	CreateFile(dbTwo, dataCountTwo, arrayTwo);
	// Test 3
	std::cout << "Test 3" << std::endl;
	for (int i = 0; i < dataCountTwo; std::cout << arrayTwo[i++] << " ");
	std::cout << std::endl;
	file = fopen(dbTwo, "rb+");
	ChangeByCriteria(file, GTZero, ChangeSign);
	fclose(file);
	ReadFile(dbTwo, dataCountTwo, array);
	for (int i = 0; i < dataCountTwo; std::cout << array[i++] << " ");
	std::cout << std::endl;
	file = fopen(dbTwo, "rb+");
	ChangeByCriteria(file, GTZero, ChangeSign);
	fclose(file);
	ReadFile(dbTwo, dataCountTwo, array);
	for (int i = 0; i < dataCountTwo; std::cout << array[i++] << " ");
	std::cout << std::endl;
	return 0;
}
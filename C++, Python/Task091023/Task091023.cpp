// Task091023.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include"Task091023.h"

int main()
{
    int** array;
    caterMemoryToArray(array, NROW, NCOL);
    randomFillArray(array, NROW, NCOL);
    printArray(array, NROW, NCOL);
    freeMemoryArray(array, NROW);
}


void caterMemoryToArray(int** &array, int a_row, int a_col) {
    array = new int* [a_row];
    for (int i = 0; i < a_row; ++i) {
        array[i] = new int[a_col];
    }
}

void randomFillArray(int** array, int a_row, int a_col, int seed) {
	mt19937 gen(seed);
	uniform_int_distribution<> distr(-100, 100);

	for (int i = 0; i < a_row; ++i)
		for (int j = 0; j < a_col; ++j) array[i][j] = distr(gen);
}


void printArray(int** array, int a_row, int a_col) {
	for (int i = 0; i < a_row; ++i, cout << endl)
		for (int j = 0; j < a_col; cout << array[i][j++] << '\t');
}

void freeMemoryArray(int** array, int a_row) {
	for (int i = 0; i < a_row; ++i)
		delete[] array[i];
	delete[] array;
}

//Домашнее задание 1: создание void - функций,
//которые :
//-отводит память;
//-задаёт случайные значения массива;
//-печатает память;
//-освобождает память;

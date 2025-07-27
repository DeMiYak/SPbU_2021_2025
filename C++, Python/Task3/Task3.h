#ifndef TASK3_H
#define TASK3_H

const int NCOL = 6;
const int NROW = 8;

#include <iostream>
#include <random>

using namespace std;

void swap(int*& a, int*& b) {
	int* temp; temp = a; a = b; b = temp;
}

// 3.1

void sortArrayByLastColStatic(int array[][NCOL], int a_row, int a_col) {
	const int temp = a_col - 1;
	for (int i = 0; i < a_row - 1; ++i)
		for (int j = 1; j < a_row - i; ++j) {
			if (array[j][temp] < array[j - 1][temp]) swap(array[j], array[j - 1]);
		}

}

void deleteRowsByLastColNegStatic(int array[][NCOL], int& a_row, int& a_col) {
	const int temp = a_col - 1;
	int negSum = 0;
	int lastPosIndex;
	bool hasNegIndex = false;
	// 0. Checking first row, last column element
	if (array[0][temp] < 0) {
		++negSum;
		hasNegIndex = true;
		lastPosIndex = 0;
	}
	else { lastPosIndex = 1; }
	for (int i = 1; i < a_row; ++i) {
		// 1. First element is positive and the others are 
		if (!hasNegIndex && array[i][temp] >= 0) { ++lastPosIndex; }
		// 2. First negative element after positives
		else if (!hasNegIndex && array[i][temp] < 0) {
			++negSum;
			hasNegIndex = true;
			lastPosIndex = i;
		}
		// 3. A continuation of negative elements
		else if (hasNegIndex && array[i][temp] < 0) { ++negSum; }
		// 4. Positive elements after the first negative one
		else {
			for (int j = 0; j < a_col; ++j) {
				array[lastPosIndex][j] = array[i][j];
			}
			++lastPosIndex;
		}
	}
	// New array row length
	a_row -= negSum;
}

void printArrayStatic(int array[][NCOL], const int a_row, const int a_col) {
	for (int i = 0; i < a_row; ++i, cout << endl)
		for (int j = 0; j < a_col; cout << array[i][j++] << '\t');
}

// 3.2

// Bubble Sort
void sortArrayByLastCol(int** array, int a_row, int a_col) {
	const int temp = a_col - 1;
	for (int i = 0; i < a_row - 1; ++i)
		for (int j = 1; j < a_row - i; ++j) {
			if (array[j][temp] < array[j - 1][temp]) swap(array[j], array[j - 1]);
		}

}

void deleteRowsByLastColNeg(int** array, int& a_row, int& a_col) {
	const int temp = a_col - 1;
	int lastPosIndex;
	int negSum = 0;
	bool hasNegIndex = false;
	// 0. Checking first row, last column element
	if (array[0][temp] < 0) {
		++negSum;
		hasNegIndex = true;
		lastPosIndex = 0;
		delete[] array[0];
	}
	else { lastPosIndex = 1; }
	for (int i = 1; i < a_row; ++i) {
		// 1. First element is positive and the others are 
		if (!hasNegIndex && array[i][temp] >= 0) { ++lastPosIndex; }
		// 2. First negative element after positives
		else if (!hasNegIndex && array[i][temp] < 0) {
			++negSum;
			hasNegIndex = true;
			lastPosIndex = i;
			delete[] array[i];
		}
		// 3. A continuation of negative elements
		else if (hasNegIndex && array[i][temp] < 0) { ++negSum; delete[] array[i]; }
		// 4. Positive elements after the first negative one
		else { array[lastPosIndex++] = array[i]; }
	}
	// New array row length
	a_row -= negSum;
}

// Supplementary work

void caterMemoryToArray(int**& array, const int a_row, const int a_col) {
	int** temp = new int* [a_row];
	for (int i = 0; i < a_row; ++i) {
		temp[i] = new int[a_col];
	}
	array = temp;
}

void randomFillArray(int** array, const int a_row, const int a_col, int seed = 1331) {
	mt19937 gen(seed);
	uniform_int_distribution<> distr(-100, 100);

	for (int i = 0; i < a_row; ++i)
		for (int j = 0; j < a_col; array[i][j++] = distr(gen));
}


void printArray(int** array, const int a_row, const int a_col) {
	for (int i = 0; i < a_row; ++i, cout << endl)
		for (int j = 0; j < a_col; cout << array[i][j++] << '\t');
}

void freeMemoryArray(int** array, const int a_row) {
	for (int i = 0; i < a_row; ++i)
		delete[] array[i];
	delete[] array;
}


#endif TASK3_H
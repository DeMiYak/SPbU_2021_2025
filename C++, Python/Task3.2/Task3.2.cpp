// Task3.2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Task3.2.h"

int main()
{
	mt19937 gen(time(0));

	int** array_1;
	int a_row, a_col;

	const char* folder = "Tests/Test";
	const char* type = ".txt";
	char* testFile = new char[BUFFER_SIZE];
	char* buffer = new char[BUFFER_SIZE];

	int randomiseNum;

	cout << "Enter number of randomly generated matrices (>= 0): ";
	cin >> randomiseNum;
	while (randomiseNum < 0) {
		cout << "Incorrect value. Try again: ";
		cin >> randomiseNum;
	}

	cout << "Sorted matrices:" << endl;

	for (int i = 1; i <= randomiseNum; ++i) {
		MakeRandomArray(a_row, a_col, array_1, gen);
		cout << "Test " << i << endl << "Before sorting:\n";
		printArray(array_1, a_row, a_col);

		cout << "After sorting:\n";
		sortArrayByLastCol(array_1, a_row, a_col);
		printArray(array_1, a_row, a_col);

		freeMemoryArray(array_1, a_row);

		cout << "End of Test " << i << endl;
	}

	cout << "Matrices with last column negative value deleted lines:" << endl;

	for (int i = 1; i < 5; ++i) {

		_itoa_s(i, buffer, 100, 10);
		strcpy_s(testFile, BUFFER_SIZE, folder);
		strcat_s(testFile, BUFFER_SIZE, buffer);
		strcat_s(testFile, BUFFER_SIZE, type);
		ReadArrayFromFile(array_1, a_row, a_col, testFile);
		cout << "Test " << i << endl << "Before deletion:\n";
		printArray(array_1, a_row, a_col);

		cout << "After deletion:\n";
		deleteRowsByLastColNeg(array_1, a_row, a_col);
		printArray(array_1, a_row, a_col);

		cout << "End of Test " << i << endl;
		strcpy_s(testFile, BUFFER_SIZE, "");
		strcpy_s(buffer, BUFFER_SIZE, "");

		freeMemoryArray(array_1, a_row);
	}

}

void Swap(int*& a, int*& b) {
	int* temp; temp = a; a = b; b = temp;
}

// Bubble Sort
void sortArrayByLastCol(int** array, int a_row, int a_col) {
	const int temp = a_col - 1;
	for (int i = 0; i < a_row - 1; ++i)
		for (int j = 1; j < a_row - i; ++j) {
			if (array[j][temp] < array[j - 1][temp]) Swap(array[j], array[j - 1]);
		}

}

void caterMemoryToArray(int**& array, const int a_row, const int a_col) {
	array = new int* [a_row];
	for (int i = 0; i < a_row; ++i) {
		array[i] = new int[a_col];
	}
}

void printArray(int** array, const int a_row, const int a_col) {
	for (int i = 0; i < a_row; ++i, cout << endl)
		for (int j = 0; j < a_col; // cout << array[i][j++] << '\t'
			printf("% 5d", array[i][j++]));
	cout << endl << endl;
}

void freeMemoryArray(int** array, const int a_row) {
	for (int i = 0; i < a_row; ++i)
		delete[] array[i];
	delete[] array;
}

void deleteRowsByLastColNeg(int** array, int& a_row, int a_col) {
	const int temp{ a_col - 1 };
	int countNeg{ 0 };
	for (int i = 0; i < a_row; ++i) {
		if (array[i][temp] < 0) ++countNeg;
		else swap(array[i], array[i - countNeg]);
	}
	
	for(int j = a_row - countNeg; j < a_row; ++j){
		delete[] array[j];
	}

	a_row -= countNeg;
}

void ReadArrayFromFile(int** &array, int& a_row, int& a_col, const char* FileName) {
	std::ifstream in(FileName);

	cout << FileName << endl;
	if (!in.is_open())
	{
		cout << "Couldn't find a file" << endl;
		return;
	}

	in >> a_row >> a_col;

	caterMemoryToArray(array, a_row, a_col);

	if (a_row > NROW || a_col > NCOL) {
		cout << "Data overload." << endl;
		a_row = 0;
		a_col = 0;
		in.close();
		return;
	}

	for (int i = 0; i < a_row; ++i) {
		for (int j = 0; j < a_col; ++j) {
			in >> array[i][j];
		}
	}
	in.close();

}

void MakeRandomArray(int& a_row, int& a_col, int** &array, mt19937& gen) {
	uniform_int_distribution<> distr(-100, 100), colDistr(1, NCOL), rowDistr(1, NROW);

	a_row = rowDistr(gen);
	a_col = colDistr(gen);

	caterMemoryToArray(array, a_row, a_col);
	for (int i = 0; i < a_row; ++i)
		for (int j = 0; j < a_col; ++j)
			array[i][j] = distr(gen);
}
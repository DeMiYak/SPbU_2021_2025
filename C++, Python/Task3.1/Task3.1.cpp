#include "Task3.1.h"

int main()
{
	mt19937 gen(time(0));

	int a_row, a_col;
	int array_1[NROW][NCOL];
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
		printArrayStatic(array_1, a_row, a_col);

		cout << "After sorting:\n";
		sortArrayByLastColStatic(array_1, a_row, a_col);
		printArrayStatic(array_1, a_row, a_col);

		cout << "End of Test " << i << endl << endl;
	}

	cout << "Matrices with last column negative value deleted lines:" << endl;

	for (int i = 1; i < 5; ++i) {

		_itoa_s(i, buffer, 100, 10);
		strcpy_s(testFile, BUFFER_SIZE, folder);
		strcat_s(testFile, BUFFER_SIZE, buffer);
		strcat_s(testFile, BUFFER_SIZE, type);
		ReadArrayFromFile(array_1, a_row, a_col, testFile);
		cout << "Test " << i << endl << "Before deletion:\n";
		printArrayStatic(array_1, a_row, a_col);

		cout << "After deletion:\n";
		deleteRowsByLastColNegStatic(array_1, a_row, a_col);
		printArrayStatic(array_1, a_row, a_col);

		cout << "End of Test " << i << endl;
		strcpy_s(testFile, BUFFER_SIZE, "");
		strcpy_s(buffer, BUFFER_SIZE, "");
	}

	delete[] testFile;
	delete[] buffer;
}

void Swap(int& a, int& b) {
	int temp; temp = a; a = b; b = temp;
}

void sortArrayByLastColStatic(int array[][NCOL], int a_row, int a_col) {
	const int tempCol = a_col - 1;
	const int tempRow = a_row - 1;
	for (int i = 0; i < tempRow; ++i)
		for (int j = 1; j < a_row - i; ++j) {
			//if (array[j][tempCol] < array[j - 1][tempCol]) Swap(array[j], array[j - 1]); // Why does this work out right?
			if (array[j][tempCol] < array[j - 1][tempCol])
				for (int k = 0; k < a_col; ++k) Swap(array[j][k], array[j-1][k]);
		}

}

void deleteRowsByLastColNegStatic(int array[][NCOL], int& a_row, int a_col) {
	const int temp{ a_col - 1 };
	int count{ 0 };
	for (int i = 0; i < a_row; ++i) {
		if (array[i][temp] < 0) ++count;
		else swap(array[i], array[i - count]);
	}
	a_row -= count;
}

void printArrayStatic(int array[][NCOL], int a_row, int a_col) {
	for (int i = 0; i < a_row; ++i, cout << endl)
		for (int j = 0; j < a_col; 
			printf("% 5d", array[i][j++]));
	
	cout << endl << endl;
}

void ReadArrayFromFile(int array[][NCOL], int& a_row, int& a_col, const char* FileName) {
	std::ifstream in(FileName);

	if (!in.is_open())
	{
		cout << "Couldn't find a file" << endl;
		return;
	}

	in >> a_row >> a_col;
	
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

void MakeRandomArray(int &a_row, int &a_col, int array[][NCOL], mt19937 &gen) {
	uniform_int_distribution<> distr(-100, 100), colDistr(1, NCOL), rowDistr(1, NROW);

	a_row = rowDistr(gen);
	a_col = colDistr(gen);

	for (int i = 0; i < a_row; ++i)
		for (int j = 0; j < a_col; ++j)
			array[i][j] = distr(gen);
}
#include "Task3.h"

int main()
{
	mt19937 gen(1331);
	uniform_int_distribution<> distr(-100, 100);

	// 3.1

	int a_row, a_col;

	int a[NROW][NCOL];
	for (a_row = 0; a_row < NROW; ++a_row) {
		for (a_col = 0; a_col < NCOL; ++a_col) {
			*(*(a + a_row) + a_col) = distr(gen);
			cout << *(*(a + a_row) + a_col) << '\t';
		}
		cout << endl;
	}

	sortArrayByLastColStatic(a, NROW, NCOL);
	deleteRowsByLastColNegStatic(a, a_row, a_col);
	deleteRowsByLastColNegStatic(a, a_row, a_col);
	cout << endl;
	printArrayStatic(a, a_row, a_col);
	a_row = NROW;

	// 3.2


	cout << endl;
	//

	int** array;
	caterMemoryToArray(array, NROW, NCOL);
	randomFillArray(array, NROW, NCOL);
	cout << "Unsorted Array: " << endl;
	printArray(array, NROW, NCOL);

	cout << endl;

	sortArrayByLastCol(array, NROW, NCOL);

	cout << "Sorted Array:" << endl;
	printArray(array, NROW, NCOL);

	freeMemoryArray(array, NROW);

	//

	cout << endl;

	int** array_2;
	caterMemoryToArray(array_2, NROW, NCOL);
	randomFillArray(array_2, NROW, NCOL);
	cout << "Shortened Array: " << endl;

	deleteRowsByLastColNeg(array_2, a_row, a_col);
	printArray(array_2, a_row, a_col);
	cout << "\na_row = " << a_row;

	freeMemoryArray(array_2, a_row);
}


// Дана матрица. упорядочить строки по величине элемента из последнего столбца.
// Удалить все строки, содержащие в последнем столбце отрицательные значения

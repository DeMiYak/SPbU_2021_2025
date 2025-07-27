#include "MineSweeper.h"
#include"MineSweeperView.h"
#include<WinUser.h>
//Поле - N * M клеток.
//Рисуется поле.На нем расставляются мины.Должно быть несколько уровней сложности.
//Ход – постановка курсора на нужную клетку и нажатие клавиши, означающий, что нужно
//сделать, поставить флажок или раскрыть клетку.Раскрытие уже раскрытой клетки означает
//«раскрыть все оставшиеся клетки вокруг нее».

/// Задачи:
/// * Добавить инструкции к управлению (ColorPrint)
/// * Обновлять только изменённые клетки (DrawMinesweeper)
/// * Поменять фон, графически оформить
/// * Разрешение экрана

void printMS(vector<vector<int>> table) {
	for (auto& i : table) {
		for (auto& j : i) {
			if (j == MineSweeper::MINE) {
				cout << "* ";
			}
			else cout << j << " ";
		}
		cout << endl;
	}
}

void printMS(vector<vector<MineSweeper::CELL_INFO>> table) {
	for (auto& i : table) {
		for (auto& j : i) { cout << j << " "; }
		cout << endl;
	}
}


int main() {
	/*CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;
	HANDLE m = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(m, &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	printf("columns: %d\n", columns);
	printf("rows: %d\n", rows);
	COORD trest = GetLargestConsoleWindowSize(m);
	std::cout << trest.X << " " << trest.Y << '\n';*/
	MineSweeper mf(8, 8, 20);
	MineSweeperView mfv(mf);
	return 0;
}


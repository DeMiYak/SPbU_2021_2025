#include "MineSweeper.h"
#include"MineSweeperView.h"
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
	MineSweeper mf(8, 8, 20);
	MineSweeperView mfv(mf);
	cout << endl;
	mf.CreateMinefield(12, 30, 180);
	//printMS(mf.GetMinefield());


	return 0;
}


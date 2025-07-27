#pragma once
#include<random>
#include<vector>

using namespace std;

/*
Идея реализации:
Создаём два класса:
Первый отвечает за графический интерфейс (GUI),
второй отвечает за игровые механики (MINESWEEPER).

GUI должен зависеть от MINESWEEPER,
MINESWEEPER, в свою очередь, содержит все 
Во втором классе нужно реализовать:


*/

//Поле - N * M клеток.
//Рисуется поле.На нем расставляются мины.Должно быть несколько уровней сложности.
//Ход – постановка курсора на нужную клетку и нажатие клавиши, означающий, что нужно
//сделать, поставить флажок или раскрыть клетку. Раскрытие уже раскрытой клетки означает
//«раскрыть все оставшиеся клетки вокруг нее».

// Уровень сложности - плотность бомб.
enum CELL_INFO {CLOSED, OPEN, FLAG};

class MineSweeper {
public:
	static const int MINE = -1;

	
	MineSweeper(int rows, int columns, int mineCount) : _rows(rows), _columns(columns), _mineCount(mineCount) {
		CreateMinefield();
	}

	const vector<vector<int>>& GetMinefield() { return _mineField; }
	
	const vector<vector<CELL_INFO>>& GetCellInfo() { return _cellInfo; }

	void CreateMinefield(int rows, int columns, int mineCount);
 
	bool OpenCell(int row, int col);

	int CountNeighbouringFlags(int row, int col);

	void Flag(int row, int col);

private:
	const vector<pair<int, int>> _offsets = {
		{-1, -1}, {-1, 0}, {-1, 1},
		{0, -1}, {0, 1},
		{1, - 1}, {1, 0}, {1, 1}
	};

	int _rows;
	int _columns;
	int _mineCount;

	vector<vector<int>> _mineField;
	vector<pair<int, int>> _mines;
	vector<vector<CELL_INFO>> _cellInfo;
	void CreateMinefield();
	// void ShowMinefield(); GUI
	void ResizeFields();
	bool CheckCoordinate(int row, int col);
	bool CheckCoordinate(pair<int, int> point, pair<int,int> offset);
	void OpenZeroCells(int row, int col);
};
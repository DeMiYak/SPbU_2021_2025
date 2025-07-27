#pragma once
#include<random>
#include<vector>

using namespace std;

/*
Идея реализации:
Создаём два класса:
Первый отвечает за графический интерфейс (MineSweeperView),
второй отвечает за игровые механики/игровую логику (MineSweeper).
*/

//Поле - N * M клеток.
//Рисуется поле.На нем расставляются мины.Должно быть несколько уровней сложности.
//Ход – постановка курсора на нужную клетку и нажатие клавиши, означающий, что нужно
//сделать, поставить флажок или раскрыть клетку. Раскрытие уже раскрытой клетки означает
//«раскрыть все оставшиеся клетки вокруг нее».

// Уровень сложности - плотность бомб.


class MineSweeper {
public:
	static const enum CELL_INFO { CLOSED, OPEN, FLAG };
	static const int MINE = -1;
	
	MineSweeper(int rows, int columns, int mineCount) : _rows(rows), _columns(columns), _mineCount(mineCount) {
		InitMinefield();
	}

	const vector<vector<int>>& GetMinefield() { return _mineField; }
	
	const vector<vector<CELL_INFO>>& GetCellInfo() { return _cellInfo; }

	const int GetRows() { return _rows; }

	const int GetColumns() { return _columns; }

	void CreateMinefield(int rows, int columns, int mineCount);
	bool OpenCell(int row, int col);
	void Flag(int row, int col);
	bool CheckCoordinate(pair<int, int> point, pair<int, int> offset);
	bool Win();
	void OpenMinefield();
private:
	const vector<pair<int, int>> _offsets = {
		{-1, -1}, {-1, 0}, {-1, 1},
		{0, -1}, {0, 1},
		{1, - 1}, {1, 0}, {1, 1}
	};

	int _rows;
	int _columns;
	int _closedCellsCount;
	int _mineCount;

	vector<vector<int>> _mineField;
	vector<vector<CELL_INFO>> _cellInfo;
	void InitMinefield();
	void ResizeFields();
	bool CheckCoordinate(int row, int col);
	int CountNeighbouringFlags(int row, int col);
	void OpenZeroCells(int row, int col);
	bool IsOpenZeroCellNeighbouring(pair<int, int> point);
};
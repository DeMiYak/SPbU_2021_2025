#include"MineSweeper.h"

#include <ctime>

void MineSweeper::CreateMinefield(int rows, int columns, int mineCount)
{
	_rows = rows;
	_columns = columns;
	_mineCount = mineCount;

	CreateMinefield();
}

bool MineSweeper::OpenCell(int row, int col)
{
	if (_cellInfo[row][col] == FLAG) return false;

	if (_cellInfo[row][col] == OPEN && CountNeighbouringFlags(row, col) >= _mineField[row][col]) {
		bool mineOpened = false;
		for (auto& offset : _offsets) {
			if (CheckCoordinate({ row, col }, offset) && _cellInfo[row + offset.first][col + offset.second] == CLOSED)
				mineOpened = mineOpened || OpenCell(row + offset.first, col + offset.second);
		}
		return mineOpened;
	}

	if (_cellInfo[row][col] == CLOSED && _mineField[row][col] == 0) {
		OpenZeroCells(row, col);
	}

	_cellInfo[row][col] = OPEN;
	return _mineField[row][col] == MINE;
}

void MineSweeper::Flag(int row, int col)
{
	if (_cellInfo[row][col] == FLAG) _cellInfo[row][col] = CLOSED;
	else if (_cellInfo[row][col] == CLOSED) _cellInfo[row][col] = FLAG;
}

int MineSweeper::CountNeighbouringFlags(int row, int col)
{
	int flagCount = 0;
	for (auto& offset : _offsets) {
		if (CheckCoordinate({ row, col }, offset) && _cellInfo[row + offset.first][row + offset.second] == FLAG) {
			++flagCount;
		}
	}
	return flagCount;
}

/// <summary>
/// Creates a Minefield with cleaning beforehand.
/// </summary>
void MineSweeper::CreateMinefield()
{
	mt19937 gen(time(0));
	uniform_int_distribution<> rowRange(0, _rows - 1), colRange(0, _columns - 1);
	
	ResizeFields();

	// Generating Mines
	for (int i = 0; i < _mineCount; ++i) {
		int n = rowRange(gen);
		int m = colRange(gen);

		while (_mineField[n][m] == MINE) {
			n = rowRange(gen);
			m = colRange(gen);
		}

		_mineField[n][m] = MINE;
		_mines[i] = { n, m };

	}

	// Generating Numbers
	for (auto& mine : _mines) {
		for (auto& offset : _offsets) {
			if (CheckCoordinate(mine, offset) && _mineField[mine.first + offset.first][mine.second + offset.second] != MINE) {
				++_mineField[mine.first + offset.first][mine.second + offset.second];
			}
		}
	}
}

void MineSweeper::OpenZeroCells(int row, int col)
{
	if (_mineField[row][col] != 0) return;
	
	vector<pair<int, int>> stack = { {row, col} };
	while (!stack.empty()) {
		pair<int, int> point = stack.back();
		stack.pop_back();
		_cellInfo[point.first][point.second] = OPEN;
		if (_mineField[point.first][point.second] == 0) {
			for (auto& offset : _offsets) {
				if (CheckCoordinate(point, offset))
					stack.push_back({point.first + offset.first, point.second + offset.second});
			}
		}
	}
}

void MineSweeper::ResizeFields()
{
	_mineField.clear();
	_mineField.resize(_rows);
	for (auto& i : _mineField) i.resize(_columns);

	_cellInfo.clear();
	_cellInfo.resize(_rows);
	for (auto& i : _cellInfo) i.resize(_columns);
	
	_mines.clear();
	_mines.resize(_mineCount);
}

bool MineSweeper::CheckCoordinate(int row, int col)
{
	return row >= 0 && col >= 0 && row < _rows && col < _columns;
}

bool MineSweeper::CheckCoordinate(pair<int, int> point, pair<int,int> offset)
{
	return CheckCoordinate(point.first + offset.first, point.second + offset.second);
}

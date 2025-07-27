#include"MineSweeper.h"

void MineSweeper::CreateMinefield(int rows, int columns, int mineCount)
{
	_rows = rows;
	_columns = columns;
	_mineCount = mineCount;

	InitMinefield();
}

bool MineSweeper::OpenCell(int row, int col)
{
	if (_cellInfo[row][col] == FLAG) return false;

	if (_cellInfo[row][col] == OPEN && CountNeighbouringFlags(row, col) >= _mineField[row][col]) {
		bool mineOpened = false;
		for (auto& offset : _offsets) {
			if (CheckCoordinate({ row, col }, offset) && _cellInfo[row + offset.first][col + offset.second] == CLOSED)
				mineOpened = OpenCell(row + offset.first, col + offset.second) || mineOpened;
		}
		return mineOpened;
	}

	if (_cellInfo[row][col] == CLOSED && _mineField[row][col] == 0) {
		OpenZeroCells(row, col);
	}

	if (_cellInfo[row][col] == CLOSED && _mineField[row][col] != 0) {
		_cellInfo[row][col] = OPEN;
		--_closedCellsCount;
	}
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
		if (CheckCoordinate({ row, col }, offset) && _cellInfo[row + offset.first][col + offset.second] == FLAG) {
			++flagCount;
		}
	}
	return flagCount;
}

/// <summary>
/// Creates a Minefield with cleaning beforehand.
/// </summary>
void MineSweeper::InitMinefield()
{
	mt19937 gen(time(0));
	uniform_int_distribution<> rowRange(0, _rows - 1), colRange(0, _columns - 1);
	
	_closedCellsCount = _columns * _rows;
	ResizeFields();
	vector<pair<int, int>> _mines(_mineCount);
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
		if (_mineField[point.first][point.second] == 0 && _cellInfo[point.first][point.second] == CLOSED) {
			for (auto& offset : _offsets) {
				// Ћибо добавить последовательный поиск в stack дл€ нахождени€ повтор€ющихс€ элементов
				// Ћибо не рассматривать те точки, которые наход€тс€ вокруг открытой нулевой
				if (CheckCoordinate(point, offset) && _cellInfo[point.first + offset.first][point.second + offset.second] == CLOSED && !IsOpenZeroCellNeighbouring({point.first + offset.first, point.second + offset.second}))
					stack.push_back({point.first + offset.first, point.second + offset.second});
			}
		}
		_cellInfo[point.first][point.second] = OPEN;
		--_closedCellsCount;
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
}

bool MineSweeper::IsOpenZeroCellNeighbouring(pair<int, int> point)
{
	for (auto& offset : _offsets) {
		if (CheckCoordinate(point, offset) &&
			_mineField[point.first + offset.first][point.second + offset.second] == 0 &&
			_cellInfo[point.first + offset.first][point.second + offset.second] == OPEN)
			return true;
	}
	return false;
}

bool MineSweeper::CheckCoordinate(int row, int col)
{
	return row >= 0 && col >= 0 && row < _rows && col < _columns;
}

bool MineSweeper::CheckCoordinate(pair<int, int> point, pair<int,int> offset)
{
	return CheckCoordinate(point.first + offset.first, point.second + offset.second);
}

bool MineSweeper::Win()
{
	return _closedCellsCount == _mineCount;
}

void MineSweeper::OpenMinefield()
{
	for (auto& i : _cellInfo) {
		for (auto& j : i) j = OPEN;
	}
}

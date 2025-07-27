#include "MineSweeperView.h"
#include<string>
void MineSweeperView::DrawMineSweeper()
{
	vector<vector<MineSweeper::CELL_INFO>> cellInfo = _mineSweeperModel.GetCellInfo();
	vector<vector<int>> mineField = _mineSweeperModel.GetMinefield();
	for (int row = 0; row < cellInfo.size(); ++row) {
		for (int col = 0; col < cellInfo[0].size(); ++col) {
			int x = 2 * col + DRAW_OFFSET.second;
			int y = row + DRAW_OFFSET.first;
			switch (cellInfo[row][col]) {
			case MineSweeper::OPEN:
				ColorPrint(x, y, B_L_BLUE, OpenCellCase(mineField[row][col]));
				break;
			case MineSweeper::CLOSED:
				ColorPrint(x, y, F_L_GREEN, CLOSED);
				break;
			case MineSweeper::FLAG:
				ColorPrint(x, y, B_L_RED, FLAG);
				break;
			}
		}
	}
	DrawCursor();
}

void MineSweeperView::DrawCursor()
{
	vector<vector<MineSweeper::CELL_INFO>> cellInfo = _mineSweeperModel.GetCellInfo();
	vector<vector<int>> mineField = _mineSweeperModel.GetMinefield();
	const char* cellChar;
	switch (cellInfo[_cursor.first][_cursor.second]) {
	case MineSweeper::OPEN:
		cellChar = OpenCellCase(mineField[_cursor.first][_cursor.second]);
		break;
	case MineSweeper::CLOSED:
		cellChar = CLOSED;
		break;
	case MineSweeper::FLAG:
		cellChar = FLAG;
		break;
	default:
		cellChar = " ";
		break;
	}
	ColorPrint(2 * _cursor.second + DRAW_OFFSET.second, _cursor.first + DRAW_OFFSET.first, B_D_WHITE, cellChar);
}

void MineSweeperView::MoveGameCursor(pair<int, int> direction)
{
	if (_mineSweeperModel.CheckCoordinate(_cursor, direction)) {
		_cursor.first += direction.first;
		_cursor.second += direction.second;
	}
}

void MineSweeperView::SetCustomParameters()
{
	int rows, columns, mines;
	do {
		cout << "Rows: ";
		cin >> rows;
	} while (rows <= 0);
	do {
		cout << "Columns: ";
		cin >> columns;
	} while (columns <= 0);
	do {
		cout << "Mines: ";
		cin >> mines;
	} while (mines <= 0);
	if (mines > columns * rows) mines = columns * rows;
	_mineSweeperModel.CreateMinefield(rows, columns, mines);
}

const char* MineSweeperView::OpenCellCase(int cellData)
{
	switch (cellData) {
	case MineSweeper::MINE:
		return MINE;
	default:
		return NUMBERS[cellData];
	}
}

void MineSweeperView::GameLoop()
{
	bool win = false;
	bool lose = false;
	ColorPrint(DRAW_OFFSET.second, DRAW_OFFSET.first + _mineSweeperModel.GetRows() + 2, F_L_WHITE, "Controls: WASD to move");
	ColorPrint(DRAW_OFFSET.second, DRAW_OFFSET.first + _mineSweeperModel.GetRows() + 3, F_L_WHITE, "K to open cells");
	ColorPrint(DRAW_OFFSET.second, DRAW_OFFSET.first + _mineSweeperModel.GetRows() + 4, F_L_WHITE, "L to flag/unflag");
	ColorPrint(DRAW_OFFSET.second, DRAW_OFFSET.first + _mineSweeperModel.GetRows() + 5, F_L_WHITE, "Hint: press K on an open cell to open surrounding cells");
	ColorPrint(DRAW_OFFSET.second, DRAW_OFFSET.first + _mineSweeperModel.GetRows() + 6, F_L_WHITE, "(Value of a cell has to be lower than a number of surrounding flags)");	while (!lose && !win) {
		DrawMineSweeper();
		char key = tolower(_getch());
		switch (key) {
		case 'w':
			MoveGameCursor({ -1, 0 });
			break;
		case 'a':
			MoveGameCursor({ 0, -1});
			break;
		case 's':
			MoveGameCursor({ 1, 0 });
			break;
		case 'd':
			MoveGameCursor({ 0, 1 });
			break;
		case 'k':
			lose = _mineSweeperModel.OpenCell(_cursor.first, _cursor.second);
			win = _mineSweeperModel.Win();
			break;
		case 'l':
			_mineSweeperModel.Flag(_cursor.first, _cursor.second);
			break;
		}
	}
	_mineSweeperModel.OpenMinefield();
	DrawMineSweeper();
	if (lose) {
		ColorPrint(DRAW_OFFSET.second, DRAW_OFFSET.first - 1, F_L_RED, "Whoops. You blew up.");
	}
	else {
		ColorPrint(DRAW_OFFSET.second, DRAW_OFFSET.first - 1, F_L_GREEN, "Yahoo! You survived.");
	}
	ColorPrint(DRAW_OFFSET.second, DRAW_OFFSET.first + _mineSweeperModel.GetRows(), F_L_WHITE, "Press any key to leave.");
	_getch();
}

void MineSweeperView::StartGame()
{
	ColorPrint(0, 0, F_L_MAGENTA, "Choose level difficulty and press \"Enter\":");
	ColorPrint(0, 1, F_L_GREEN, "1. Beginner");
	ColorPrint(0, 2, F_L_YELLOW, "2. Intermediate");
	ColorPrint(0, 3, F_L_RED, "3. Expert");
	ColorPrint(0, 4, F_L_WHITE, "4. Custom");
	ColorPrint(0, 5, F_L_CYAN, "5. Exit");
	MoveCursor(0, 6);
	string c;
	bool condition = false;
	while (!condition)
	{
		condition = true;
		cin >> c;
		switch (c[0])
		{
		case '1':
			_mineSweeperModel.CreateMinefield(9, 9, 10);
			break;
		case '2':
			_mineSweeperModel.CreateMinefield(16, 16, 40);
			break;
		case '3':
			_mineSweeperModel.CreateMinefield(16, 30, 99);
			break;
		case '4':
			SetCustomParameters();
			break;
		case '5':
			exit(0);
		default:
			condition = false;
			cout << "Incorrect input. Please choose the difficulty level: ";
			break;
		}
	}
	ClearConsole();
	VisibleCursor(false);
	GameLoop();
	ClearConsole();
	StartGame();
}

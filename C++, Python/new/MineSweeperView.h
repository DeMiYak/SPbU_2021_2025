#pragma once
#include<iostream>
#include"Minesweeper.h"
#include"conio.h"
#include "Console.h"

using namespace std;

class MineSweeperView {
public:
	void PrintMS(vector<vector<int>> table) {
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

	void PrintMS(vector<vector<MineSweeper::CELL_INFO>> table) {
		for (auto& i : table) {
			for (auto& j : i) { cout << j << " "; }
			cout << endl;
		}
	}
	MineSweeperView(MineSweeper mineSweeperModel) : _mineSweeperModel(mineSweeperModel) {
		
		InitConsole("Minesweeper", GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
		StartGame();
	};
private:
	const char* CLOSED = "X";
	const char* FLAG = ">";
	const char* MINE = "*";
	const char* NUMBERS[9] = {" ", "1", "2", "3", "4", "5", "6", "7", "8"};
	const pair<int, int> DRAW_OFFSET = { 2, 30 };

	MineSweeper _mineSweeperModel;
	pair<int, int> _cursor;

	const char* OpenCellCase(int cellData);
	void GameLoop();
	void StartGame();
	void DrawMineSweeper();
	void DrawCursor();
	void MoveGameCursor(pair<int, int> direction);
	void SetCustomParameters();
};

#pragma once
#include<iostream>
#include"Minesweeper.h"
#include"StdAfx.h"
#include<map>
#include<string>

using namespace std;

class MineSweeperView {
public:
	MineSweeperView(MineSweeper mineSweeperModel);
	void DrawMineSweeper();
		
private:
	const map<CELL_INFO, char> _set = {
		{OPEN, ' '},
		{CLOSED, 'X'},
		{FLAG, '>'},
	};
	const string MINE = "*";
	const string ZERO = " ";

	MineSweeper _mineSweeperModel;


	string OpenCellCase(int cellData);
};

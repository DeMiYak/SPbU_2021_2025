#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Console.h"
#include "Position.h"

using uint = int;

struct Cell
{
	char c;
	COLORS color;

	Cell() : c('0'), color(F_D_CYAN) {};
	void draw(Position& pos);
	void draw(uint x, uint y);
};
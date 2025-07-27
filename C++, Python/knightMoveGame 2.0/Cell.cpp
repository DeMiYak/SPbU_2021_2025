#include "Cell.h"

void Cell::draw(Position& pos)
{
	char str[2];
	sprintf(str, "%c", c);
	ColorPrint(pos.y, pos.x, color, str);
}

void Cell::draw(uint x, uint y)
{
	char str[2];
	sprintf(str, "%c", c);
	ColorPrint(y, x, color, str);
}
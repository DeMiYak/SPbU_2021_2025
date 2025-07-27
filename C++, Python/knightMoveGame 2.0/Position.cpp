#include "Position.h"

Position Position::operator=(const Position& p)
{
    x = p.x;
    y = p.y;
    return *this;
}

Position& Position::operator+=(const Position& p)
{
    x += p.x;
    y += p.y;
    return *this;
}


Position operator+(const Position& p1, const Position& p2)
{
    Position res(p1);
    res += p2;
    return res;
}

bool operator==(const Position& p1, const Position& p2)
{
    return p1.x == p2.x && p1.y == p2.y;
}

bool operator!=(const Position& p1, const Position& p2)
{
    return !(p1.x == p2.x && p1.y == p2.y);
}

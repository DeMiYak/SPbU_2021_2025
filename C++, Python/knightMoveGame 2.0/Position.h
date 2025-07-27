#pragma once
struct Position
{
    int x;
    int y;

    Position() : x(-1), y(-1) {};

    Position(int x, int y) : x(x), y(y) {};

    Position(const Position& p) : x(p.x), y(p.y) {};

    Position& operator+=(const Position& p);

    Position operator=(const Position& p);

    friend Position operator+(const Position& p1, const Position& p2);

    friend bool operator==(const Position& p1, const Position& p2);
    friend bool operator!=(const Position& p1, const Position& p2);
};
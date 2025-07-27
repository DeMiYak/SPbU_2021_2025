#pragma once

#include <iostream>
#include <vector>
#include "Position.h"
#include <windows.h>
#include "Cell.h"

using namespace std;

using uint = int;
const uint NCOL = 30 + 2;
const uint NROW = 15 + 2;
const double ISLAND_PROBABILITY = 0.3;
const double PATH_LENGTH_MULT = 0.005;
const Position START(NROW - 2, 1);
const Position FINISH(1, NCOL - 2);
const Position ALL_POSSIBLE_STEPS[8] =
{ Position(-2, -1), Position(-2, 1), Position(-1, 2), Position(1, 2),
  Position(2, 1), Position(2, -1),Position(1, -2), Position(-1, -2) };

class Map
{
private:
    Cell field[NROW][NCOL];
    vector<Position> path;
    vector<Position> PossibleFillingPosition = vector<Position>(8);

    bool isFinishInPossibleFillingPosition();

    void getPossibleFillingPosition(const Position currentPosition, const Position previousPosition);

    double calculateInverseDistance(const Position& pos);

    uint chooseFromPossibleFillingPosition();

    void initialize();

    void generate_path();

    void createNoiseIslands();

public:

    uint getPathLenght();

    void highlightPath();

    bool isIsland(Position& pos);

    void setIsland(Position& pos);

    void setKnightPos(Position& pos);

    void setHighlightIsland(Position& pos);

    void clearHighlightIslands(vector<Position>& possibleSteps);

    void setHighlightIslands(vector<Position>& possibleSteps);

    void setExtraHighlightIsland(Position& pos);

    void clearExtraHighlightIsland(Position& pos);

    void create();

    void draw();

    void update(Position& pos);

    void update(vector<Position>& pos);
};

bool isInMap(Position position);
#pragma once

#include <conio.h>
#include <time.h>
#include "Map.h"


using namespace std;

class Game
{
    Map map;
    uint currentPossibleStepIndex;
    Position knightPos = START;
    Position previousKnightPos = Position(-1, -1);
    vector<Position> possibleSteps = vector<Position>(8);
    enum class GameType { FIRST, SECOND } type;
    uint pathLength;
    uint stepNum = 0;
    bool gameover = false;

    void setGameType();

    bool isMoveValidForSecondType(const Position& target);

    void moveKnight();

    void choosePositionToMove(char key);

    void getPossibleSteps();

    void getNextPossibleStepIndex();

    void getPreviousPossibleStepIndex();

    void handleChooseKey(char key);

    void handleMoveKey(char key);

    void handleF10Key();

    void handleSpecialKey();

    void catchUserActions();

    bool isStepNumAcceptable();

    void printHelp();

public:

    void go();

};
#include "Game.h"

void Game::setGameType()
{
    cout << "Choose the type of game: " << endl;
    cout << "1. The number of moves is limited by " << pathLength << " steps" << endl;
    cout << "2. You can't go back to the island you just came from" << endl;
    cout << "Press 1 or 2: ";
    char c;
    bool condition = true;
    while (condition)
    {
        cin >> c;
        switch (c)
        {
        case '1': type = GameType::FIRST;
            condition = false;
            break;
        case '2': type = GameType::SECOND;
            condition = false;
            break;
        default:
            cout << "Press 1 or 2: ";
            break;
        }
    }
    system("cls");
}

bool Game::isMoveValidForSecondType(const Position& target)
{
    return (type != GameType::SECOND || target != previousKnightPos);
}

void Game::choosePositionToMove(char key)
{
    map.clearExtraHighlightIsland(possibleSteps[currentPossibleStepIndex]);
    switch (key)
    {
    case 'd':
        getNextPossibleStepIndex();
        break;
    case 'a':
        getPreviousPossibleStepIndex();
        break;
    default:
        break;
    }
    map.setExtraHighlightIsland(possibleSteps[currentPossibleStepIndex]);
}

void Game::moveKnight()
{
    previousKnightPos = knightPos;
    knightPos = possibleSteps[currentPossibleStepIndex];
    map.clearHighlightIslands(possibleSteps);
    map.setIsland(previousKnightPos);
    map.setKnightPos(knightPos);
    ++stepNum;
}

void Game::getPossibleSteps()
{
    possibleSteps.clear();
    for (uint i = 0; i < 8; ++i)
    {
        Position tmp = knightPos + ALL_POSSIBLE_STEPS[i];
        if (isInMap(tmp) && map.isIsland(tmp) && isMoveValidForSecondType(tmp))
            possibleSteps.push_back(tmp);
    }
}

void Game::getNextPossibleStepIndex()
{
    if (++currentPossibleStepIndex > possibleSteps.size() - 1)
        currentPossibleStepIndex = 0;
}

void Game::getPreviousPossibleStepIndex()
{
    if (--currentPossibleStepIndex < 0)
        currentPossibleStepIndex = possibleSteps.size() - 1;
}

void Game::handleF10Key()
{
    map.clearHighlightIslands(possibleSteps);
    map.setIsland(knightPos);
    map.update(possibleSteps);
    map.update(knightPos);
    map.highlightPath();
    gameover = true;
}

void Game::handleSpecialKey()
{
    char key = _getch();
    switch (key)
    {
    case 'D':
        handleF10Key();
        break;
    default:
        break;
    }
}

void Game::handleMoveKey(char key)
{
    moveKnight();
    map.update(possibleSteps);
    map.update(knightPos);
    map.update(previousKnightPos);
}

void Game::handleChooseKey(char key)
{
    choosePositionToMove(key);
    map.update(possibleSteps);
}

void Game::catchUserActions()
{
    bool tookStep = false;
    while (!gameover && !tookStep)
    {
        char key = tolower(_getch());
        switch (key)
        {
        case 'a':
        case 'd':
            handleChooseKey(key);
            break;
        case 13:
            handleMoveKey(key);
            tookStep = true;
            break;
        case 0:
            handleSpecialKey();
            break;
        default:
            break;
        }
    }
}

bool Game::isStepNumAcceptable()
{
    return (type != GameType::FIRST || stepNum <= pathLength);
}

void Game::printHelp()
{
    ColorPrint(NCOL + 2, 0, F_L_RED, "Only EN keyboard!");
    ColorPrint(NCOL + 2, 1, F_L_RED, "F10 to highlight path to finish");
    ColorPrint(NCOL + 2, 2, F_L_RED, "a-d to select a position for a move");
}

void Game::go()
{
    InitConsole("Game");
    VisibleCursor(false);
    map.create();
    pathLength = 1.5 * map.getPathLenght();
    setGameType();
    map.setKnightPos(knightPos);
    map.draw();
    printHelp();
    MoveCursor(0, NROW);
    if (type == GameType::FIRST)
        cout << stepNum << "/" << pathLength << endl;

    while (knightPos != FINISH && !gameover && isStepNumAcceptable())
    {
        getPossibleSteps();
        // возможно, что попадем в позицию из которой нет выхода при втором режим игры
        if (possibleSteps.empty())
            break;

        currentPossibleStepIndex = 0;
        map.setHighlightIslands(possibleSteps);
        map.setExtraHighlightIsland(possibleSteps[currentPossibleStepIndex]);
        map.update(possibleSteps);

        catchUserActions();

       MoveCursor(0, NROW);
       if (type == GameType::FIRST)
           cout << stepNum << "/" << pathLength << endl;
    }
    if (knightPos == FINISH)
        ColorPrint(0, NROW, F_L_GREEN, "You Won");
    else
        ColorPrint(0, NROW, F_L_RED, "Vechnaya Pamyat");
}
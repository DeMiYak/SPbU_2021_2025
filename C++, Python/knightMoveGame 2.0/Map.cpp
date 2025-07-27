#include "Map.h"

bool isInMap(Position position)
{
    return (position.x > 0 && position.x < NROW - 1) && (position.y > 0 && position.y < NCOL - 1);
}

bool Map::isFinishInPossibleFillingPosition()
{
    for (auto& step : PossibleFillingPosition)
        if (step.x == FINISH.x && step.y == FINISH.y)
            return true;
    return false;
}

bool Map::isIsland(Position& pos)
{
    return field[pos.x][pos.y].c != '0';
}

void Map::getPossibleFillingPosition(const Position currentPosition, const Position previousPosition)
{
    PossibleFillingPosition.clear();
    for (uint i = 0; i < 8; ++i)
    {
        Position tmp = currentPosition + ALL_POSSIBLE_STEPS[i];
        if (isInMap(tmp) && !isIsland(tmp))
            PossibleFillingPosition.push_back(tmp);
    }

    if (PossibleFillingPosition.size()) return;
    //Если не нашлось место для нового острова, то разрешаем перейти на старый, но не предыдущий
    for (uint i = 0; i < 8; ++i)
    {
        Position tmp = currentPosition + ALL_POSSIBLE_STEPS[i];
        if (isInMap(tmp) && tmp != previousPosition)
            PossibleFillingPosition.push_back(tmp);
    }
}

double Map::calculateInverseDistance(const Position& pos)
{
    double distance = abs(pos.x - FINISH.x) + abs(pos.y - FINISH.y);
    return 1.0 / distance;
}

uint Map::chooseFromPossibleFillingPosition()
{
    uint closestIndex = 0;
    uint possibleStepsNum = PossibleFillingPosition.size();
    double closestDistance = calculateInverseDistance(PossibleFillingPosition[0]);
    double probabilitySum = closestDistance;

    for (size_t i = 1; i < possibleStepsNum; ++i)
    {
        double distance = calculateInverseDistance(PossibleFillingPosition[i]);
        probabilitySum += distance;
        if (distance > closestDistance)
        {
            closestIndex = i;
            closestDistance = distance;
        }
    }

    double randomValue = static_cast<double>(rand()) / RAND_MAX * probabilitySum;

    if (randomValue < calculateInverseDistance(PossibleFillingPosition[closestIndex]) *
        exp(static_cast<double>(path.size()) * PATH_LENGTH_MULT))
        return closestIndex;

    uint randomIndex = closestIndex;
    while (randomIndex == closestIndex)
        randomIndex = rand() % possibleStepsNum;

    return randomIndex;
}

void Map::setIsland(Position& pos)
{
    field[pos.x][pos.y].c = 'I';
    field[pos.x][pos.y].color = F_D_YELLOW;
}

void Map::setKnightPos(Position& pos)
{
    field[pos.x][pos.y].c = 'K';
    field[pos.x][pos.y].color = F_L_RED;
}

void Map::setHighlightIsland(Position& pos)
{
    field[pos.x][pos.y].color = F_D_GREEN;
}

void Map::setExtraHighlightIsland(Position& pos)
{
    field[pos.x][pos.y].color = B_D_GREEN;
}

void Map::clearExtraHighlightIsland(Position& pos)
{
    field[pos.x][pos.y].color = F_D_GREEN;
}

void Map::setHighlightIslands(vector<Position>& possibleSteps)
{
    for (auto& pos : possibleSteps)
        setHighlightIsland(pos);
}

void Map::clearHighlightIslands(vector<Position>& possibleSteps)
{
    for (auto& pos : possibleSteps)
        setIsland(pos);
}

void Map::initialize()
{
    for (uint k = 0; k < NCOL; ++k)
        field[0][k].c = '-';
    for (uint i = 1; i < NROW - 1; ++i)
    {
        field[i][0].c = '|';
        field[i][NCOL - 1].c = '|';
    }
    for (uint k = 0; k < NCOL; ++k)
        field[NROW - 1][k].c = '-';
}

void Map::generate_path()
{
    path.push_back(START);
    setIsland(path.back());
    getPossibleFillingPosition(path.back(), Position(-1, -1));
    do
    {
        path.push_back(PossibleFillingPosition[chooseFromPossibleFillingPosition()]);
        setIsland(path.back());
        getPossibleFillingPosition(path.back(), path[path.size() - 2]);
    } while (!isFinishInPossibleFillingPosition());
    path.push_back(FINISH);
    setIsland(path.back());
}

void Map::createNoiseIslands()
{
    for (uint i = 1; i < NROW - 1; ++i)
    {
        for (uint j = 1; j < NCOL - 1; ++j)
        {
            double randomValue = static_cast<double>(rand()) / RAND_MAX;
            if (randomValue < ISLAND_PROBABILITY)
            {
                field[i][j].c = 'I';
                field[i][j].color = F_D_YELLOW;
            }
        }
    }
}

void Map::create()
{
    initialize();
    generate_path();
    createNoiseIslands();
}

void Map::draw()
{
    for (uint i = 0; i < NROW; ++i)
    {
        for (uint j = 0; j < NCOL; ++j)
            field[i][j].draw(i, j);
        cout << endl;
    }
}

void Map::update(Position& pos)
{
    field[pos.x][pos.y].draw(pos);
}

void Map::update(vector<Position>& posList)
{
    for (auto& pos : posList)
        update(pos);
}

void Map::highlightPath()
{
    for (auto& pos : path)
    {
        setHighlightIsland(pos);
        Sleep(100);
        update(pos);
    }
}

uint Map::getPathLenght()
{
    return path.size();
}

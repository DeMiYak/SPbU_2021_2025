
#include "Distribution.h"

/// <summary>
/// Создаёт гипергеометрическое распределение с
/// теоретическими вероятностями
/// </summary>
/// <param name="_whBalls">Белые шарики</param>
/// <param name="_blBalls">Чёрные шарики</param>
/// <param name="_pickNum">Число вытаскиваний</param>
Distribution::Distribution(int _whBalls, int _blBalls, int _pickNum) : 
    whBalls(_whBalls), 
    blBalls(_blBalls), 
    pickNum(_pickNum), 
    thProb(nullptr)
{
    int condBall = blBalls >= pickNum && whBalls >= pickNum;
    int condPick = pickNum > 0 && blBalls > 0 && whBalls > 0;
    int error = 0;
    if (!condBall) {
        std::cout << "Ошибка: число вытаскиваний не должно превосходить числа чёрных или белых шариков";
        error = 1;
    }
    if (!condPick) {
        std::cout << "Ошибка: число вытаскиваний, чёрных и белых шариков должно быть положительным (>0)";
        error = 1;
    }
    if (error) {
        exit(1);
    }
    TheorProb();
}

/// <summary>
/// Устанавливает параметры для гипергеометрического распределения
/// и меняет теоретические вероятности
/// </summary>
/// <param name="_whBalls">Белые шарики</param>
/// <param name="_blBalls">Чёрные шарики</param>
/// <param name="_pickNum">Число вытаскиваний</param>
void Distribution::SetParameters(int _whBalls, int _blBalls, int _pickNum)
{
    whBalls = _whBalls;
    blBalls = _blBalls;
    pickNum = _pickNum;
    int condBall = blBalls >= pickNum && whBalls >= pickNum;
    int condPick = pickNum > 0 && blBalls > 0 && whBalls > 0;
    int error = 0;
    if (!condBall) {
        std::cout << "Ошибка: число вытаскиваний не должно превосходить числа чёрных или белых шариков";
        error = 1;
    }
    if (!condPick) {
        std::cout << "Ошибка: число вытаскиваний, чёрных и белых шариков должно быть положительным (>0)";
        error = 1;
    }
    if (error) {
        exit(1);
    }
    TheorProb();
}

/// <summary>
/// Возвращает имя распределения
/// </summary>
/// <returns>Указатель на имя распределения</returns>
const wchar_t* Distribution::GetName()
{
    return L"Гипергеометрическое распределение";
}


/// <summary>
/// Считает теоретические вероятности распределения
/// </summary>
void Distribution::TheorProb()
{
    delete[] thProb;
    thProb = new double[pickNum + 1];
    int totalBalls = whBalls + blBalls;
    double prob = 1;

    for (int k = 0; k < pickNum; k++) prob *= double(blBalls - k) / (totalBalls - k);
    thProb[0] = prob;
    for (int i = 1; i <= pickNum; i++) {
        int k = i - 1;
        prob = prob * (whBalls - k) * (pickNum - k) / ((k + 1) * (blBalls - pickNum + k + 1));
        thProb[i] = prob;
    }
}

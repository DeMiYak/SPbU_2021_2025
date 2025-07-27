// CTask4CompWork.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Fisher-Yates algorithm 


#include <iostream>
#include "FYA.h"
using namespace std;
//void Print(int* arr, int length)
//{
//    std::cout << "{ " << arr[0] << ", ";
//    for (int i = 1; i < length - 1; ++i) {
//        std::cout << arr[i] << ", ";
//    }
//    std::cout << arr[length - 1] << " }" << std::endl;
//}

int main()
{
    int len = 30, k = 3;
    int num = 10e5;
    FYInterface interface(len, k);
    // i-позиции (Хи-квадрат)
    // C-k циклы
    interface.CountOnePermutation();
    interface.Print();
    interface.ResetCycles();
    interface.CountPermutations(num);
    interface.Print();
    // Теоретическая частота: EC-k = 1/k
    // Эмпирическая частота...
    // По теореме Фишера можно представить распределение
    cout << endl;
    Test();
}

// 4. Реализовать моделирование случайной перестановки 
// с помощью метода Фишера - Йетса на C++.Промоделировать 
// перестановку много(~10 ^ 5 - ~10 ^ 7) раз, проверить 
// распределение перестановок с помощью распределения позиции 
// i - го элемента и числа циклов длины k для малых и больших 
// длин перестановок(пользуясь соотношениями, упомянутыми на паре, 
// и критерием Хи - квадрат).
#include <iostream>
#include <random>
#include"SampleModelling.h"
#include"BernHypGeomSampleGenerator.h"
#include"InvFunHypGeomSampleGenerator.h"
#include"Distribution.h"
#include"Method.h"
#include"Chi2Histogram.h"
#include"PROBDIST.h"
using namespace std;

/// <summary>
/// Приложение main для демонстрации классов
/// </summary>
int main()
{
    setlocale(LC_ALL, "Russian");
    // Начало HOWTO
    // 
    // Рассмотрим класс гипергеометрических распределений Distribution
    // Начнём с описания параметров, необходимых для конструктора класса
    // 
    // Число белых шариков. При расчёте теоретических вероятностей
    // гипергеометрического распределения смотрим на то, сколько белых
    // шариков вытащили из общей кучи
    int whBalls = 20;
    // Число чёрных шариков. Дополняют общую кучу из белых и чёрных шариков
    int blBalls = 30;
    // Число вытаскиваний. Определяют, сколько раз подряд вытаскивали
    // шарики из общей кучи без возврата.
    int pickNum = 10;

    // Объяснив поля класса Distribution, перейдём к конструктору
    // Первым параметр - число белых шариков,
    // Второй параметр - число чёрных шариков,
    // Третий параметр - число вытаскиваний.
    // В ходе работы конструктора вычисляются
    // теоретические вероятности (thProb) распределения при
    // заданных параметрах (whBalls, blBalls, pickNum).
    Distribution d0(whBalls, blBalls, pickNum);

    //¡Замечание: если параметры не указываются, то 
    // распределение строится с такими значениями!
    // whBalls = 20;
    // blBalls = 30;
    // pickNum = 10;
    // 
    //¡Замечание: есть варианты, при которых конструктор выведет ошибку!
    // 1. Если число белых/чёрных шариков или число вытаскиваний <= 0;
    // 2. Если число белых/чёрных шариков меньше числа вытаскиваний
    // 
    // Что можно делать с классом Distribution?
    // 
    // Можно извлекать параметры используя Get...()
    // Например:
    // 
    // Белые шарики
    int exWhBalls(d0.GetWhBalls());
    // Чёрные шарики
    int exBlBalls(d0.GetBlBalls());

    // Может возникнуть естественное желание просмотреть
    // теоретические вероятности распределения из Distribution.
    // Для этого понадобится число вытаскиваний (pickNum),
    // так как размер массива теоретических вероятностей зависит
    // от него,
    // и сам массив теоретических вероятностей (thProb), откуда
    // будут браться теоретические вероятности.
    // 
    // Число вытаскиваний
    int exPickNum(d0.GetPickNum());
    // Теоретические вероятности
    const double* thProb = d0.GetThProb();

    // Выведем теоретические вероятности
    // (заметим, что число вытащенных белых шариков
    // колеблется от 0 до pickNum).
    std::cout << "Пример вывода теоретических вероятностей: [" << thProb[0];
    for (int i = 1; i < exPickNum + 1; i++) {
        std::cout << ", " << thProb[i];
    }
    std::cout << "]\n" << std::endl;


    // Можно менять параметры распределения, пользуясь
    // SetParameters(...).
    // 
    // Например:
    int newWhBalls = 40;
    int newBlBalls = 35;
    int newPickNum = 20;
    // В ходе изменения параметров распределения стоит учитывать,
    // что также пересчитываются теоретические вероятности
    // распределения, поскольку меняются параметры.
    d0.SetParameters(newWhBalls, newBlBalls, newPickNum);

    //¡Замечание: есть варианты, при которых SetParameters выведет ошибку!
    // 1. Если число белых/чёрных шариков или число вытаскиваний <= 0;
    // 2. Если число белых/чёрных шариков меньше числа вытаскиваний
    // 
    // Можно вывести название распределения через GetName()
    // Например:

    std::wcout << L"Данные о распределении (Distribution):\n" << L"Имя распределения: " << d0.GetName();

    // Можно вывести содержимое распределения, пользуясь оператором<<.
    // Например:
    std::cout << d0;

    // Кроме того, в некоторых случаях может пригодиться присваивание
    // или конструирование распределения через другие
    // Например:
    Distribution d1(d0), d2;
    d2 = d0;


    // Рассмотрим следующий класс - абстрактный базовый
    // класс генерации выборки BaseSampleGenerator.
    //  
    // Опишем параметры, используемые в BaseSampleGenerator
    // для конструктора.
    // 
    // Объём выборки. Определяет размер выборки
    int samVol = 100;

    // Распределение из класса Distribution.
    // (Напомним, что в конструкторе и при SetParameters(...)
    // следующий порядок:
    // 1. Белые шарики
    // 2. Чёрные шарики
    // 3. Число вытаскиваний
    Distribution d3(20, 30, 10);

    // От абстрактного базового класса BaseSampleGenerator
    // наследуется два класса с полиморфизмом: 
    // BernHypGeomSampleGenerator - класс генератора выборки
    // методом распределений Бернулли;
    // InvFunHypGeomSampleGenerator - класс генератора выборки
    // методом обратных функций. 
    //
    // В конструктор классов генераторов выборки есть два варианта: 
    // если ввести только:
    // Первый параметр - объём выборки (samVol), 
    // то получится пустая выборка - то есть, выделится память для выборки (sample)
    // и сохраниться объём выборки (samVol); 
    // если ввести: 
    // Первый параметр - объём выборки (samVol)
    // Второй параметр - распределение (d0),
    // то выборка будет построена на основании распределения (d0).

    BaseSampleGenerator* bsg = nullptr;
    int pick = rand() % 2;
    switch (pick) {
    case 0:
        bsg = new BernHypGeomSampleGenerator(samVol, d3);
        break;
    case 1:
        bsg = new InvFunHypGeomSampleGenerator(samVol, d3);
        break;
    }
    //¡Замечание: поскольку для конструктора выделяется память под выборку,
    // при задании объёма выборки samVol < 0 будет ошибка!
    // 
    // Как можно использовать ...SampleGenerator?
    // 
    // Можно извлечь параметры, используя Get...()
    // 
    // Может возникнуть естественное желание просмотреть
    // выборку из BaseSampleGenerator.
    // Для этого понадобится объём выборки (samVol),
    // так как размер выборки зависит
    // от него,
    // и саму выборку (sample), откуда
    // будут браться выборочные значения
    const int* sample = bsg->GetSample();
    int exSamVol = bsg->GetSamVol();

    // Выведем значения выборки
    std::cout << "\nПример вывода выборки: [" << sample[0];
    for (int i = 1; i < exSamVol; i++) {
        std::cout << ", " << sample[i];
    }
    std::cout << "]\n" << std::endl;

    // Можно построить выборку, пользуясь Simulate(...),
    // Первый параметр - распределение из Distribution,
    // Второй параметр - объём выборки.
    Distribution d4(30, 40, 15);
    int demoSamVol = 300;
    bsg->Simulate(d4, demoSamVol);

    // А затем вывести выборку
    std::cout << "\nПример вывода выборки: [" << sample[0];
    for (int i = 1; i < demoSamVol; i++) {
        std::cout << ", " << sample[i];
    }
    std::cout << "]\n" << std::endl;

    // Также можно просто вывести выборку и её объём, используя оператор<<
    std::cout << "\nДанные о выборке (BaseSampleGenerator):\n" << *bsg;

    // Также стоит рассмотреть классы-наследники
    // BernHypGeomSampleGenerator 
    // и
    // InvFunHypGeomSampleGenerator.
    // 
    // Начнём с BernHypGeomSampleGenerator
    // 
    // Класс создаётся точно также как и в случае с BaseSampleGenerator.
    // В качестве конструктора приведём альтернативный вариант, тот,
    // в котором отсутствует распределение из Distribution
    int samVol1 = 500;
    // Напомним, что конструктор без параметров объявляет их
    // с такими значениями:
    // 1. Белых шариков - 20;
    // 2. Чёрных шариков - 30;
    // 3. Вытаскиваний - 10;
    Distribution d5;
    BernHypGeomSampleGenerator bern(samVol1);
    bern.Simulate(d5, samVol1);

    // Аналогично BaseSampleGenerator, можно пользоваться Get...(),
    // и выводить выборку с её объёмом:
    // 
    // Может возникнуть естественное желание просмотреть
    // выборку из BernHypGeomSampleGenerator.
    // Для этого понадобится объём выборки (samVol),
    // так как размер выборки зависит
    // от него,
    // и саму выборку (sample), откуда
    // будут браться выборочные значения
    const int* bernSample = bern.GetSample();
    int bernSamVol = bern.GetSamVol();

    // А затем вывести выборку
    std::cout << "\nПример вывода выборки: [" << bernSample[0];
    for (int i = 1; i < bernSamVol; i++) {
        std::cout << ", " << bernSample[i];
    }
    std::cout << "]\n" << std::endl;

    // Либо просто воспользоваться оператором<<
    std::cout << bern;

    // Для InvFunHypGeomSampleGenerator:
    // Класс создаётся точно также как и в случае с BaseSampleGenerator.
    // В качестве конструктора приведём альтернативный вариант, тот,
    // в котором отсутствует распределение из Distribution
    int samVol2 = 500;
    // Напомним, что конструктор без параметров объявляет их
    // с такими значениями:
    // 1. Белых шариков - 20;
    // 2. Чёрных шариков - 30;
    // 3. Вытаскиваний - 10;
    Distribution d6;
    InvFunHypGeomSampleGenerator invfun(samVol2);
    invfun.Simulate(d6, samVol2);

    // Аналогично BaseSampleGenerator, можно пользоваться Get...(),
    // и выводить выборку с её объёмом:

    // Может возникнуть естественное желание просмотреть
    // выборку из BernHypGeomSampleGenerator.
    // Для этого понадобится объём выборки (samVol),
    // так как размер выборки зависит
    // от него,
    // и саму выборку (sample), откуда
    // будут браться выборочные значения
    const int* invfunSample = invfun.GetSample();
    int invfunSamVol = invfun.GetSamVol();

    // А затем вывести выборку
    std::cout << "\nПример вывода выборки: [" << invfunSample[0];
    for (int i = 1; i < invfunSamVol; i++) {
        std::cout << ", " << invfunSample[i];
    }
    std::cout << "]\n" << std::endl;

    // Либо просто воспользоваться оператором<<
    std::cout << invfun;

    // Перейдём к следующему классу - классу ChiSqHistogram.
    // В нём хранятся эмпирические и теоретические частоты 
    // некоторого распределения из класса Distribution с выборкой из
    // BaseSampleGenerator, а также диапазон частот, значение хи-квадрата,
    // число степеней свободы и пороговый уровень (p_level)
    // 
    // В конструктор поступают:
    // Первый параметр - выборка "после эксперимента", то есть, после
    // того как мы используем Simulate(..) или используем конструктор с
    // классом параметром Distribution;
    // Второй параметр - распределение Distribution.
    // из выборки будет построены эмпирические частоты, а из распределения - 
    // теоретические частоты.
    // 
    // bsgChi - выборка "после эксперимента,
    // Пример конструирования bsgChi:
    int whBallsBSG = 70;
    int blBallsBSG = 80;
    int pickNumBSG = 32;
    Distribution dBSG(whBallsBSG, blBallsBSG, pickNumBSG);
    int samVolBSG = 150;
    BaseSampleGenerator* bsgChi = nullptr;
    int pickBSG = rand() % 2;
    switch (pickBSG) {
    case 0:
        bsgChi = new BernHypGeomSampleGenerator(samVolBSG, dBSG);
        break;
    case 1:
        bsgChi = new InvFunHypGeomSampleGenerator(samVolBSG, dBSG);
        break;
    }
    Distribution dChi(50, 40, 32);
    // dChi - распределение из Distribution.
    //
    // При использовании конструктора не вычисляются:
    // 1. Пороговый уровень (pLevel);
    // 2. Значение хи-квадрата (chiSq);
    // 3. Число степеней свободы (dof);
    ChiSqHistogram csh(bsg, d0);
    

    //¡Замечание: предполагается, что для конструктора диапазон частот выборки bsg
    // будет либо совпадать с диапазоном частот (число вытаскиваний + 1) распределения 
    // d0, либо будет меньше. Иначе ошибка, поскольку значения выборки выходят
    // за теоретический диапазон частот!
    // TODO: p_value = 0, dof = -1, chiSq = -1 в этом случае

    // Что можно делать с классом ChiSqHistogram?
    // 
    // Можно извлекать параметры, используя Get...().
    // Например:
    // Число степеней свободы.
    int dof = csh.GetDegreeOfFreedom();
    // Значение хи-квадрата
    double chiSq = csh.GetChi();
    // Пороговый уровень
    double p_level = csh.GetPLevel();

    // Может возникнуть естественное желание просмотреть
    // эмпирические (empFreq) и теоретические (thFreq) частоты.
    // Для этого понадобится объём выборки (samVol),
    // так как размер выборки зависит
    // от него,
    // и сами массивы частот (empFreq,, thFreq), откуда
    // будут браться частотные значения
    // 
    // Диапазон частот. Задаёт размер empFreq, thFreq.
    int freqLen = csh.GetFreqLen();
    // Массив эмпирических частот
    const int* empFreq = csh.GetEmpFreq();
    // Массив теоретических частот
    const double* thFreq = csh.GetThFreq();

    // А затем вывести эмпирические частоты
    std::cout << "\nПример вывода эмпирических частот: [" << empFreq[0];
    for (int i = 1; i < freqLen; i++) {
        std::cout << ", " << empFreq[i];
    }
    std::cout << "]\n" << std::endl;

    // и теоретические частоты
    std::cout << "\nПример вывода теоретических частот: [" << thFreq[0];
    for (int i = 1; i < freqLen; i++) {
        std::cout << ", " << thFreq[i];
    }
    std::cout << "]\n" << std::endl;

    // Либо просто воспользоваться оператором<<
    std::cout << csh;

    // Можно поменять данные, пользуясь функцией SetData(...)
    // Первый параметр - выборка "после эксперимента"
    // Второй параметр - распределение
    int samVolEx = 500;
    BaseSampleGenerator* bsgEx = new BernHypGeomSampleGenerator(samVolEx);
    Distribution dEx;
    bsgEx->Simulate(dEx, samVolEx);
    ChiSqHistogram cshEx;
    cshEx.SetData(bsgEx, dEx);
    // А затем можно произвести вычисление хи-квадрата, числа степеней свободы и
    // порогового уровня, характеризующих отношение между эмпирической
    // (empFreq) и теоретической (thFreq) частотами.
    //
    cshEx.CalcChiSq();
    std::cout << "\nПример вывода содержимого из ChiSqHistogram после CalcChiSq\n" << cshEx;
    delete bsgEx;

    // Стоит отметить, что присутствует и перечисляемый тип Method,
    // используемый при выборе метода моделирования выборки
    // 
    // BD - Bernoulli Distribution - распределение Бернулли
    Method methodBD(BD);
    // IF - Inverse Function - метод обратной функции
    Method methodIF(IF);

    // Где может использоваться?
    // Когда хотим задать классу BaseSampleGenerator определённый метод
    // моделирования выборки
    Method methodRand = static_cast<Method>(rand() % 2);
    delete bsg;
    switch (methodRand) {
    case BD:
        bsg = new BernHypGeomSampleGenerator(samVol);
        break;
    case IF:
        bsg = new InvFunHypGeomSampleGenerator(samVol);
        break;
    }
    //...делаем что-то с bsg, а затем освобождаем память.
    delete bsg;
    delete bsgChi;

    // Конец HOWTO
}

/**
@mainpage Приложение main для демонстрации классов
<h2>Краткая сводка по классам:</h2>
<p>
- <h3>Distribution - распределение</h3>
Класс Distribution задаёт гипергеометрическое распределение и
рассчитывает теоретические вероятности для него.
- <h3>Генераторы выборки</h3>
Классы BernHypGeomSampleGenerator и InvFunHypGeomSampleGenerator, наследуемые
от абстрактного базового класса BaseSampleGenerator, представляют собой
генераторы выборок, использующих метод распределения Бернулли и метод обратных
функций соответственно. Выборки генерируются на основании распределения.
- <h3>Анализ теоретических и эмпирических частот</h3>
Класс ChiSqHistogram использует генератор выборки и распределения для
построения эмпирических и теоретических распределений соответственно, и
рассчитывает значение хи-квадрата, p-level и число степеней свобод относительно
них.
</p>

Пример использования классов с пояснениями: 
@code
#include <iostream>
#include <random>
#include"SampleModelling.h"
#include"BernHypGeomSampleGenerator.h"
#include"InvFunHypGeomSampleGenerator.h"
#include"Distribution.h"
#include"Method.h"
#include"Chi2Histogram.h"
#include"PROBDIST.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    // Начало HOWTO
    //
    // Рассмотрим класс гипергеометрических распределений Distribution
    // Начнём с описания параметров, необходимых для конструктора класса
    //
    // Число белых шариков. При расчёте теоретических вероятностей
    // гипергеометрического распределения смотрим на то, сколько белых
    // шариков вытащили из общей кучи
    int whBalls = 20;
    // Число чёрных шариков. Дополняют общую кучу из белых и чёрных шариков
    int blBalls = 30;
    // Число вытаскиваний. Определяют, сколько раз подряд вытаскивали
    // шарики из общей кучи без возврата.
    int pickNum = 10;

    // Объяснив поля класса Distribution, перейдём к конструктору
    // Первым параметр - число белых шариков,
    // Второй параметр - число чёрных шариков,
    // Третий параметр - число вытаскиваний.
    // В ходе работы конструктора вычисляются
    // теоретические вероятности (thProb) распределения при
    // заданных параметрах (whBalls, blBalls, pickNum).
    Distribution d0(whBalls, blBalls, pickNum);

    //¡Замечание: если параметры не указываются, то
    // распределение строится с такими значениями!
    // whBalls = 20;
    // blBalls = 30;
    // pickNum = 10;
    //
    //¡Замечание: есть варианты, при которых конструктор выведет ошибку!
    // 1. Если число белых/чёрных шариков или число вытаскиваний <= 0;
    // 2. Если число белых/чёрных шариков меньше числа вытаскиваний
    //
    // Что можно делать с классом Distribution?
    //
    // Можно извлекать параметры используя Get...()
    // Например:
    //
    // Белые шарики
    int exWhBalls(d0.GetWhBalls());
    // Чёрные шарики
    int exBlBalls(d0.GetBlBalls());

    // Может возникнуть естественное желание просмотреть
    // теоретические вероятности распределения из Distribution.
    // Для этого понадобится число вытаскиваний (pickNum),
    // так как размер массива теоретических вероятностей зависит
    // от него,
    // и сам массив теоретических вероятностей (thProb), откуда
    // будут браться теоретические вероятности.
    //
    // Число вытаскиваний
    int exPickNum(d0.GetPickNum());
    // Теоретические вероятности
    const double* thProb = d0.GetThProb();

    // Выведем теоретические вероятности
    // (заметим, что число вытащенных белых шариков
    // колеблется от 0 до pickNum).
    std::cout << "Пример вывода теоретических вероятностей: [" << thProb[0];
    for (int i = 1; i < exPickNum + 1; i++) {
        std::cout << ", " << thProb[i];
    }
    std::cout << "]\n" << std::endl;


    // Можно менять параметры распределения, пользуясь
    // SetParameters(...).
    //
    // Например:
    int newWhBalls = 40;
    int newBlBalls = 35;
    int newPickNum = 20;
    // В ходе изменения параметров распределения стоит учитывать,
    // что также пересчитываются теоретические вероятности
    // распределения, поскольку меняются параметры.
    d0.SetParameters(newWhBalls, newBlBalls, newPickNum);

    //¡Замечание: есть варианты, при которых SetParameters выведет ошибку!
    // 1. Если число белых/чёрных шариков или число вытаскиваний <= 0;
    // 2. Если число белых/чёрных шариков меньше числа вытаскиваний
    //
    // Можно вывести название распределения через GetName()
    // Например:

    std::wcout << L"Данные о распределении (Distribution):\n" << L"Имя распределения: " << d0.GetName();

    // Можно вывести содержимое распределения, пользуясь оператором<<.
    // Например:
    std::cout << d0;

    // Кроме того, в некоторых случаях может пригодиться присваивание
    // или конструирование распределения через другие
    // Например:
    Distribution d1(d0), d2;
    d2 = d0;


    // Рассмотрим следующий класс - абстрактный базовый
    // класс генерации выборки BaseSampleGenerator.
    //
    // Опишем параметры, используемые в BaseSampleGenerator
    // для конструктора.
    //
    // Объём выборки. Определяет размер выборки
    int samVol = 100;

    // Распределение из класса Distribution.
    // (Напомним, что в конструкторе и при SetParameters(...)
    // следующий порядок:
    // 1. Белые шарики
    // 2. Чёрные шарики
    // 3. Число вытаскиваний
    Distribution d3(20, 30, 10);

    // От абстрактного базового класса BaseSampleGenerator
    // наследуется два класса с полиморфизмом:
    // BernHypGeomSampleGenerator - класс генератора выборки
    // методом распределений Бернулли;
    // InvFunHypGeomSampleGenerator - класс генератора выборки
    // методом обратных функций.
    //
    // В конструктор классов генераторов выборки есть два варианта:
    // если ввести только:
    // Первый параметр - объём выборки (samVol),
    // то получится пустая выборка - то есть, выделится память для выборки (sample)
    // и сохраниться объём выборки (samVol);
    // если ввести:
    // Первый параметр - объём выборки (samVol)
    // Второй параметр - распределение (d0),
    // то выборка будет построена на основании распределения (d0).

    BaseSampleGenerator* bsg = nullptr;
    int pick = rand() % 2;
    switch (pick) {
    case 0:
        bsg = new BernHypGeomSampleGenerator(samVol, d3);
        break;
    case 1:
        bsg = new InvFunHypGeomSampleGenerator(samVol, d3);
        break;
    }
    //¡Замечание: поскольку для конструктора выделяется память под выборку,
    // при задании объёма выборки samVol < 0 будет ошибка!
    //
    // Как можно использовать ...SampleGenerator?
    //
    // Можно извлечь параметры, используя Get...()
    //
    // Может возникнуть естественное желание просмотреть
    // выборку из BaseSampleGenerator.
    // Для этого понадобится объём выборки (samVol),
    // так как размер выборки зависит
    // от него,
    // и саму выборку (sample), откуда
    // будут браться выборочные значения
    const int* sample = bsg->GetSample();
    int exSamVol = bsg->GetSamVol();

    // Выведем значения выборки
    std::cout << "\nПример вывода выборки: [" << sample[0];
    for (int i = 1; i < exSamVol; i++) {
        std::cout << ", " << sample[i];
    }
    std::cout << "]\n" << std::endl;

    // Можно построить выборку, пользуясь Simulate(...),
    // Первый параметр - распределение из Distribution,
    // Второй параметр - объём выборки.
    Distribution d4(30, 40, 15);
    int demoSamVol = 300;
    bsg->Simulate(d4, demoSamVol);

    // А затем вывести выборку
    std::cout << "\nПример вывода выборки: [" << sample[0];
    for (int i = 1; i < demoSamVol; i++) {
        std::cout << ", " << sample[i];
    }
    std::cout << "]\n" << std::endl;

    // Также можно просто вывести выборку и её объём, используя оператор<<
    std::cout << "\nДанные о выборке (BaseSampleGenerator):\n" << *bsg;

    // Также стоит рассмотреть классы-наследники
    // BernHypGeomSampleGenerator
    // и
    // InvFunHypGeomSampleGenerator.
    //
    // Начнём с BernHypGeomSampleGenerator
    //
    // Класс создаётся точно также как и в случае с BaseSampleGenerator.
    // В качестве конструктора приведём альтернативный вариант, тот,
    // в котором отсутствует распределение из Distribution
    int samVol1 = 500;
    // Напомним, что конструктор без параметров объявляет их
    // с такими значениями:
    // 1. Белых шариков - 20;
    // 2. Чёрных шариков - 30;
    // 3. Вытаскиваний - 10;
    Distribution d5;
    BernHypGeomSampleGenerator bern(samVol1);
    bern.Simulate(d5, samVol1);

    // Аналогично BaseSampleGenerator, можно пользоваться Get...(),
    // и выводить выборку с её объёмом:
    //
    // Может возникнуть естественное желание просмотреть
    // выборку из BernHypGeomSampleGenerator.
    // Для этого понадобится объём выборки (samVol),
    // так как размер выборки зависит
    // от него,
    // и саму выборку (sample), откуда
    // будут браться выборочные значения
    const int* bernSample = bern.GetSample();
    int bernSamVol = bern.GetSamVol();

    // А затем вывести выборку
    std::cout << "\nПример вывода выборки: [" << bernSample[0];
    for (int i = 1; i < bernSamVol; i++) {
        std::cout << ", " << bernSample[i];
    }
    std::cout << "]\n" << std::endl;

    // Либо просто воспользоваться оператором<<
    std::cout << bern;

    // Для InvFunHypGeomSampleGenerator:
    // Класс создаётся точно также как и в случае с BaseSampleGenerator.
    // В качестве конструктора приведём альтернативный вариант, тот,
    // в котором отсутствует распределение из Distribution
    int samVol2 = 500;
    // Напомним, что конструктор без параметров объявляет их
    // с такими значениями:
    // 1. Белых шариков - 20;
    // 2. Чёрных шариков - 30;
    // 3. Вытаскиваний - 10;
    Distribution d6;
    InvFunHypGeomSampleGenerator invfun(samVol2);
    invfun.Simulate(d6, samVol2);

    // Аналогично BaseSampleGenerator, можно пользоваться Get...(),
    // и выводить выборку с её объёмом:

    // Может возникнуть естественное желание просмотреть
    // выборку из BernHypGeomSampleGenerator.
    // Для этого понадобится объём выборки (samVol),
    // так как размер выборки зависит
    // от него,
    // и саму выборку (sample), откуда
    // будут браться выборочные значения
    const int* invfunSample = invfun.GetSample();
    int invfunSamVol = invfun.GetSamVol();

    // А затем вывести выборку
    std::cout << "\nПример вывода выборки: [" << invfunSample[0];
    for (int i = 1; i < invfunSamVol; i++) {
        std::cout << ", " << invfunSample[i];
    }
    std::cout << "]\n" << std::endl;

    // Либо просто воспользоваться оператором<<
    std::cout << invfun;

    // Перейдём к следующему классу - классу ChiSqHistogram.
    // В нём хранятся эмпирические и теоретические частоты
    // некоторого распределения из класса Distribution с выборкой из
    // BaseSampleGenerator, а также диапазон частот, значение хи-квадрата,
    // число степеней свободы и пороговый уровень (p_level)
    //
    // В конструктор поступают:
    // Первый параметр - выборка "после эксперимента", то есть, после
    // того как мы используем Simulate(..) или используем конструктор с
    // классом параметром Distribution;
    // Второй параметр - распределение Distribution.
    // из выборки будет построены эмпирические частоты, а из распределения -
    // теоретические частоты.
    //
    // bsgChi - выборка "после эксперимента,
    // Пример конструирования bsgChi:
    int whBallsBSG = 70;
    int blBallsBSG = 80;
    int pickNumBSG = 32;
    Distribution dBSG(whBallsBSG, blBallsBSG, pickNumBSG);
    int samVolBSG = 150;
    BaseSampleGenerator* bsgChi = nullptr;
    int pickBSG = rand() % 2;
    switch (pickBSG) {
    case 0:
        bsgChi = new BernHypGeomSampleGenerator(samVolBSG, dBSG);
        break;
    case 1:
        bsgChi = new InvFunHypGeomSampleGenerator(samVolBSG, dBSG);
        break;
    }
    Distribution dChi(50, 40, 32);
    // dChi - распределение из Distribution.
    //
    // При использовании конструктора не вычисляются:
    // 1. Пороговый уровень (pLevel);
    // 2. Значение хи-квадрата (chiSq);
    // 3. Число степеней свободы (dof);
    ChiSqHistogram csh(bsg, d0);


    //¡Замечание: предполагается, что для конструктора диапазон частот выборки bsg
    // будет либо совпадать с диапазоном частот (число вытаскиваний + 1) распределения
    // d0, либо будет меньше. Иначе ошибка, поскольку значения выборки выходят
    // за теоретический диапазон частот!
    // TODO: p_value = 0, dof = -1, chiSq = -1 в этом случае

    // Что можно делать с классом ChiSqHistogram?
    //
    // Можно извлекать параметры, используя Get...().
    // Например:
    // Число степеней свободы.
    int dof = csh.GetDegreeOfFreedom();
    // Значение хи-квадрата
    double chiSq = csh.GetChi();
    // Пороговый уровень
    double p_level = csh.GetPLevel();

    // Может возникнуть естественное желание просмотреть
    // эмпирические (empFreq) и теоретические (thFreq) частоты.
    // Для этого понадобится объём выборки (samVol),
    // так как размер выборки зависит
    // от него,
    // и сами массивы частот (empFreq,, thFreq), откуда
    // будут браться частотные значения
    //
    // Диапазон частот. Задаёт размер empFreq, thFreq.
    int freqLen = csh.GetFreqLen();
    // Массив эмпирических частот
    const int* empFreq = csh.GetEmpFreq();
    // Массив теоретических частот
    const double* thFreq = csh.GetThFreq();

    // А затем вывести эмпирические частоты
    std::cout << "\nПример вывода эмпирических частот: [" << empFreq[0];
    for (int i = 1; i < freqLen; i++) {
        std::cout << ", " << empFreq[i];
    }
    std::cout << "]\n" << std::endl;

    // и теоретические частоты
    std::cout << "\nПример вывода теоретических частот: [" << thFreq[0];
    for (int i = 1; i < freqLen; i++) {
        std::cout << ", " << thFreq[i];
    }
    std::cout << "]\n" << std::endl;

    // Либо просто воспользоваться оператором<<
    std::cout << csh;

    // Можно поменять данные, пользуясь функцией SetData(...)
    // Первый параметр - выборка "после эксперимента"
    // Второй параметр - распределение
    int samVolEx = 500;
    BaseSampleGenerator* bsgEx = new BernHypGeomSampleGenerator(samVolEx);
    Distribution dEx;
    bsgEx->Simulate(dEx, samVolEx);
    ChiSqHistogram cshEx;
    cshEx.SetData(bsgEx, dEx);
    // А затем можно произвести вычисление хи-квадрата, числа степеней свободы и
    // порогового уровня, характеризующих отношение между эмпирической
    // (empFreq) и теоретической (thFreq) частотами.
    //
    cshEx.CalcChiSq();
    std::cout << "\nПример вывода содержимого из ChiSqHistogram после CalcChiSq\n" << cshEx;
    delete bsgEx;

    // Стоит отметить, что присутствует и перечисляемый тип Method,
    // используемый при выборе метода моделирования выборки
    //
    // BD - Bernoulli Distribution - распределение Бернулли
    Method methodBD(BD);
    // IF - Inverse Function - метод обратной функции
    Method methodIF(IF);

    // Где может использоваться?
    // Когда хотим задать классу BaseSampleGenerator определённый метод
    // моделирования выборки
    Method methodRand = static_cast<Method>(rand() % 2);
    delete bsg;
    switch (methodRand) {
    case BD:
        bsg = new BernHypGeomSampleGenerator(samVol);
        break;
    case IF:
        bsg = new InvFunHypGeomSampleGenerator(samVol);
        break;
    }
    //...делаем что-то с bsg, а затем освобождаем память.
    delete bsg;
    delete bsgChi;

    // Конец HOWTO
}
@endcode
*/
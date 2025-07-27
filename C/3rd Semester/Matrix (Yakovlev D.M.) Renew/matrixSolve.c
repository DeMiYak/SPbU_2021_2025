#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>
#include<math.h>
#include"matrixInitFunc.h"
#include"matrixStruct.h"
#include"matrixOper.h"

/**
* Операции со строками
      умножение строки матрицы на число
      сложение двух строк
      перестановка строк
      (не обязательно, для большей эффективности метода Гаусса: выделение строки в другую матрицу 1*n - присваивание, без выделения памяти, прибавление к строке матрицы другой матрицы 1*n и т.п.)

4. Задачи с матрицами
   * Метод Гаусса
     - решение системы уравнений (вход: n*n матрица, 1*n столбец свободных членов, 1*n матрица для записи результата, выход:  1*n столбец решений или NULL если матрица необратима)
     - обращение квадратной матрицы

     Учитывать проблему малых знаменателей (перестановка строк или лучше вести массив индексов порядка строк).

    Сделать автоматическую проверку умножением с некоторой точностью eps.


   * Матричная норма (максимум суммы модулей элементов строки по всем строкам или максимум суммы модулей элементов стролбца по всем столбцам)

   * Матричная экспонента
      exp A = E + A + A^2/2 +...+ A^n/n! +... =  a0 + a1 + ... + an +...

     a0 = E
     an = a_{n-1} * A / n

    Остановиться на ||an|| < eps


    Для проверки:


      1 0 0        e 0    0
      0 2 0   ->   0 e^2  0
      0 0 -1       0 0    1/e



Задачи следует разбивать на модули (модуль для структуры, для операций, для метода Гаусса, для ряда и т.д.).

Следить за const.


Имена функций не обязательно такие, как указаны, но следует использовать префиксный подход: "имямодуля_имяфункции" для всех идентификаторов (чтобы исключить конфликт имен при подключении различных модулей и библиотек к одной программе).

Дедлайн - середина семестра (будет объявлен позже).
*/
/**
* Метод Гаусса
     - решение системы уравнений (вход: n*n матрица, 1*n столбец свободных членов, 1*n матрица для записи результата, выход:  1*n столбец решений или NULL если матрица необратима)
     - обращение квадратной матрицы

     Учитывать проблему малых знаменателей (перестановка строк или лучше вести массив индексов порядка строк).

    Сделать автоматическую проверку умножением с некоторой точностью eps.
*/
//Dyn
/*
matrixDyn * matrixDyn_Gauss_Method(matrixDyn *m, matrixDyn *ext)
{
    if(!m || m->vert != m->hor || !ext || ext->vert != m->vert || ext->hor != 1) return NULL;
    matrixDyn *result = matrixDyn_alloc(ext->vert, ext->hor);
    if(!result) return NULL;
    // Прямой ход Гаусса
    // Идея: проходим первые элементы строк в поисках ненулевого элемента
    // Если его нет, возвращаем NULL, если же есть - меняем позиции 0 и i строк
    // Затем выполняем вычитание, после чего рассматриваем матрицу n-1 x n-1 и повторяем так до 1 х 1
    for(size_t i = 0; i < m->vert; ++i)
    {
        size_t maxInd = i;
        double cfntMax = *(*(m->mat + i) + i);
        for(size_t j = i; j < m->vert; ++j) // Поиск ненулевого элемента
        {
            double cfnt = *(*(m->mat + j) + i);
            if(cfnt > cfntMax)
            {
                cfntMax = cfnt;
                maxInd = j;
            }
        }
        matrixDyn_swap_row(m, maxInd, i);
        matrixDyn_swap_row(ext, maxInd, i);
        double cfnt1 = *(*(m->mat + i) + i);
        // Обнуляем все элементы столбца ниже i-ого элемента
        for(size_t k = i + 1; k < m->vert; ++k)
        {
            double cfnt2 = -(*(*(m->mat + k) + i)/cfnt1);
            if(cfnt2)
            {
                matrixDyn_add_row_scalar(m, k, i, cfnt2);
                matrixDyn_add_row_scalar(ext, k, i, cfnt2);
            }
            *(*(m->mat + k) + i) = 0;
        }
    }

    // Обратный ход Гаусса
    matrixDyn_mult_scalar_row(ext, ext->vert - 1, 1.0/(*(*(m->mat + m->vert - 1) + m->vert - 1)));
    for(size_t i = m->vert - 2; i >= 0; --i)
    {
        double cfnt = *(*(m->mat + i) + i);
        if(cfnt)
        {
            for(size_t j = m->vert - 1; j > i; --j)
            {
                double cfntJ = -(*(*(m->mat + i) + j))*(**(ext->mat + j));
                **(ext->mat + i) += cfntJ;
            }
            matrixDyn_mult_scalar_row(ext, i, 1.0/cfnt);
        } else
        {
            printf("No solutions");
            return NULL;
        }
    }
    for(size_t k = 0; k < ext->vert; ++k)
    {
        **(result->mat + k) = **(ext->mat + k);
    }
}

double matrixDyn_Norm(matrixDyn *m)
{
    if(!m) return 0;
    double **ptr = m->mat, **ptrEnd = m->mat + m->vert;
    double sumCurr = 0;
    for(; ptr < ptrEnd; ++ptr)
    {
        double sumTemp = 0;
        double *ptrHor = *ptr, *ptrHorEnd = *ptr + m->hor;
        for(; ptrHor < ptrHorEnd; ++ptrHor)
        {
            sumTemp += fabs(*ptrHor);
        }
        if(sumTemp > sumCurr) sumCurr = sumTemp;
    }
    return sumCurr;
}

matrixDyn * matrixDyn_Taylor_Exp(matrixDyn *m, double eps)
{
    if(!m) return NULL;
    // 0
    matrixDyn *a0 = (matrixDyn *) matrixDyn_alloc(m->vert, m->hor);
    matrixDyn *a1 = (matrixDyn *) matrixDyn_clone(m);
    matrixDyn *a2 = (matrixDyn *) matrixDyn_alloc(m->vert, m->hor);
    matrixDyn *aClone = (matrixDyn *) matrixDyn_clone(m);
    if(!a0 || !a1 || !a2 || !aClone) return NULL;
    matrixDyn_identity(a0);
    // 1
    int n = 1;
    if(matrixDyn_Norm(aClone) < eps)
    {
        return a0;
    }
    else
    {
        matrixDyn_add(a0, m);
        a2 = matrixDyn_mult_matrixes((const matrixDyn *) a1, (const matrixDyn *) matrixDyn_mult_scalar_all(aClone, 1.0/n));
    }
    while(matrixDyn_Norm(a2) >= eps)
    {
        a0 = matrixDyn_add(a0, (const matrixDyn *) a2);
        a1 = matrixDyn_clone((const matrixDyn *) a2);
        aClone = matrixDyn_clone(m);
        a2 = matrixDyn_mult_matrixes((const matrixDyn *) a1, (const matrixDyn *) matrixDyn_mult_scalar_all(aClone, 1.0/n));
        ++n;
    }
    return a0;
}
*/

//Line
matrixLine *matrixLine_Gauss_Method(matrixLine *m, matrixLine *ext)
{
    if(!m || m->vert != m->hor || !ext || ext->vert != m->vert || ext->hor != 1) return NULL;
    matrixLine *result = matrixLine_alloc(ext->vert, ext->hor);
    if(!result) return NULL;
    // Прямой ход Гаусса
    // Идея: проходим первые элементы строк в поисках ненулевого элемента
    // Если его нет, возвращаем NULL, если же есть - меняем позиции 0 и i строк
    // Затем выполняем вычитание, после чего рассматриваем матрицу n-1 x n-1 и повторяем так до 1 х 1
    printf("\n|| Phase 1 ||\n");
    for(size_t i = 0; i < m->vert; ++i)
    {
        printf("\n|==| i = %Iu |==|\n", i);
        size_t maxInd = i;
        double cfntMax = *(m->mat + i*m->hor + i);
        for(size_t j = i; j < m->vert; ++j) // Поиск ненулевого элемента
        {
            double cfnt = fabs(*(m->mat + j*m->hor + i));
            if(cfnt > cfntMax)
            {
                cfntMax = cfnt;
                maxInd = j;
            }
        }
        printf("maxInd = %Iu\n", maxInd);
        matrixLine_swap_row(m, maxInd, i);
        matrixLine_swap_row(ext, maxInd, i);
        printf("m:\n");
        matrixLine_print(m);
        printf("\next:\n");
        matrixLine_print(ext);
        double cfnt1 = *(m->mat + i*m->hor + i);
        // printf("\ncfnt1 = %lf", cfnt1);
        // Обнуляем все элементы столбца ниже i-ого элемента
        for(size_t k = i + 1; k < m->vert; ++k)
        {
            double cfnt2 = -(*(m->mat + k*m->hor + i)/cfnt1);
            if(cfnt2)
            {
                matrixLine_add_row_scalar(m, k, i, cfnt2);
                matrixLine_add_row_scalar(ext, k, i, cfnt2);
            }
            *(m->mat + k*m->hor + i) = 0;
        }
        printf("\n|==| |==|\n");
        int d;
        scanf("%d", &d);
    }
    printf("|| Phase 2 ||");
    if(!(*(m->mat + m->vert*m->hor - 1)) && *(ext->mat + ext->vert*ext->hor - 1))
    {
        printf("No solutions");
        return NULL;
    }
    else
    {
        matrixLine_mult_scalar_row(ext, ext->vert - 1, 1.0/(*(m->mat + m->vert*m->hor - 1)));
        *(m->mat + m->vert*m->hor - 1) = 1;
    }
    for(size_t i = m->vert - 1; i > 0; --i)
    {
        printf("\n|==| i = %Iu |==|\n", i);
        size_t jpos = i - 1;
        for(size_t j = m->hor - 1; j > jpos; --j)
        {
            double cfnt1 = -(*(m->mat + jpos*m->hor + j));
            // printf("\nj = %Iu\ncfnt1 = %lf\n", j, cfnt1);
            if(cfnt1)
            {
                matrixLine_add_row_scalar(ext, jpos, j, cfnt1);
            }
            *(m->mat + jpos*m->hor + j) = 0;
        }
        double cfnt2 = *(m->mat + jpos*m->hor + jpos);
        double cfntExt = *(ext->mat);
        printf("\ncfnt2 = %lf\ncfntExt = %lf", cfnt2, cfntExt);
        if(!cfnt2)
        {
            printf("\n\nNo solutions\n\n");
            return NULL;
        }
        else
        {
            matrixLine_mult_scalar_row(ext, jpos, 1.0/cfnt2);
            *(m->mat + jpos*m->hor + jpos) = 1;
        }
        printf("\nm:\n");
        matrixLine_print(m);
        printf("\next:\n");
        matrixLine_print(ext);
        printf("\n|==| |==|\n");
        int d;
        scanf("%d", &d);
    }
    double *ptrExt = ext->mat, *ptrExtEnd = ext->mat + ext->vert;
    double *ptrResult = result->mat;
    while(ptrExt < ptrExtEnd)
    {
        *(ptrResult++) = *(ptrExt++);
    }
    return result;
}

double matrixLine_Norm(matrixLine *m)
{
    if(!m) return 0;
    double *ptr = m->mat, *ptrEnd = m->mat + m->vert*m->hor;
    double sumCurr = 0, sumTemp = 0;
    for(; ptr < ptrEnd; ++ptr)
    {
        if((ptr - m->mat) % m->hor == 0)
        {
            if(sumTemp > sumCurr) sumCurr = sumTemp;
            sumTemp = fabs(*ptr);
        }
        else sumTemp += fabs(*ptr);
    }
    return sumCurr;
}

matrixLine * matrixLine_Taylor_Exp(const matrixLine *m, double eps)
{
    if(!m) return NULL;
    // Шаг 0.
    matrixLine *a0 = matrixLine_alloc(m->vert, m->hor); // Сумма матриц
    matrixLine *a1 = matrixLine_clone(m);
    if(!a0 || !a1) return NULL;
    matrixLine_identity(a0);
    size_t n = 2;
    // Шаг 1 и так далее.


    while(matrixLine_Norm(a1) >= eps)
    {
        a0 = matrixLine_add(a0, (const matrixLine *) a1);
        a1 = matrixLine_mult_matrixes_Taylor((const matrixLine *) a1, m);
        matrixLine_mult_scalar_all(a1, 1.0/n);
        ++n;
    }
    printf("\nNorm = %lf\nEps = %lf\n", matrixLine_Norm(a1), eps);
    matrixLine_free(a1);
    return a0;
}

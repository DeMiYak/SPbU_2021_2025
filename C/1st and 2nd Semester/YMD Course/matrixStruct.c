#include<stdio.h>
#include<stdlib.h>
#include"matrixStruct.h"
#include"matrixInitFunc.h"
#include"matrixSolve.h"
/** MatrixStruct

1. Структура "Матрица" m*n
   (a) двумерный статический массив N*N; m,n < N
   (b) динамический массив с массивом индексов
   (с) одномерный массив с индексацией - обязательно

  "Поддержка" структуры
   * Создание матрицы (выделение памяти)
      struct matrix * matrix_alloc (size_t h, size_t w);
      возвращает указатель на struct matrix или NULL, если выделение памяти не удалось

   * Освобождение матрицы (free)

   * Создание матрицы как копии (клонирование) - аналог инициализации через существующую матрицу
      struct matrix * matrix_clone (const struct matrix *m);

   * Изменение размера
     struct matrix * matrix_resize (struct matrix *m);
     возвращает m или NULL при ошибке
     данные матрицы не сохраняются

   * Доступ по индексу (нумерация с 0 иди с 1, как удобнее)


     double * matrix_get (struct matrix *m, size_t i, size_t j);
     const double * matrix_cget (const struct matrix *m, size_t i, size_t j);

     по желанию - безопасный доступ (с проверкой индекса и возвратом NULL)

Реализовать структуру в виде неполного типа и трех вариантов данных функций в трех разных .c файлах (можно менять вручную или настройками проекта выбирать какой подключается) или выбирать нужный код с помощью директив (по желанию, обязательно - неполный тип и вариант (c)).
*/

// Linear
matrixLine *matrixLine_alloc(size_t i, size_t j)
{
    if(!i || !j) return NULL;
    matrixLine *m = (matrixLine *)malloc(sizeof(matrixLine));
    m->vert = i;
    m->hor = j;
    m->mat = (double*)malloc(sizeof(double)*m->vert*m->hor);
    return m;
}

matrixLine *matrixLine_clone(const matrixLine *m)
{
    matrixLine *mCpy = (matrixLine*)malloc(sizeof(matrixLine));
    if(!mCpy) return NULL;
    mCpy->vert = m->vert;
    mCpy->hor = m->hor;
    mCpy->mat = malloc(mCpy->hor*mCpy->vert*sizeof(double));
    double *ptrM = mCpy->mat, *ptrMEnd = mCpy->mat + m->vert*m->hor, *ptr = m->mat;
    while(ptrM < ptrMEnd)
    {
        *(ptrM++) = *(ptr++);
    }
    return mCpy;
}

void matrixLine_free(matrixLine *m)
{
    free(m->mat);
    free(m);
}

double *matrixLine_get(matrixLine *m, size_t i, size_t j)
{
    if(i >= m->vert || j >= m->hor) return NULL;
    return (double *) m->mat + i*m->hor + j;
}

const double *matrixLine_cget(matrixLine *m, size_t i, size_t j)
{
    if(i >= m->vert || j >= m->hor) return NULL;
    return (const double *) m->mat + i*m->hor + j;
}

matrixLine *matrixLine_resize(matrixLine *m, size_t i, size_t j)
{
    // 123|456|789 => 12|45|78 (12|34|56) => 1200|4500|7800 (12|45|78|00|00|00) => 1200|4500|7800)
    if(i == 0 || j == 0) return NULL;
    matrixLine *m1 = matrixLine_alloc(i, j);
    if(!m1) return NULL;
    matrixLine_set_zero(m1);
    size_t minHor = m->hor > j ? j : m->hor, minVert = m->vert > i ? i : m->vert;
    double *ptrM = m->mat, *ptrEndM = m->mat + minVert;
    for(; ptrM < ptrEndM; ++ptrM)
    {
        double *ptrRow = m->mat + (ptrM - m->mat)*m->hor, *ptrRowEnd = m->mat + (ptrM - m->mat)*m->hor + minHor;
        double *ptrRowM1 = m1->mat + (ptrM - m->mat)*m1->hor;
        while(ptrRow < ptrRowEnd)
        {
            *(ptrRowM1++) = *(ptrRow++);
        }
    }
    matrixLine_free(m);
    return m1;
}

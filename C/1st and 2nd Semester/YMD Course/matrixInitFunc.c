#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include"matrixInitFunc.h"
#include"matrixStruct.h"
/** matrixInitFunc

2. Функции инициализации и присваивания матрицы
    Функции инициализации создают матрицу через matrix_alloc
    Функции присваивания задают значения имеющейся матрицы
    (Могут быть реализованы через доступ по индексу или с реальным доступом к полям структуры в 4 вариантах).

   * Нулевая матрица
      struct matrix * matrix_set_zero (struct matrix *m);
      возвращает m
      struct matrix * matrix_alloc_zero (size_t h, size_t w);
      возвращает новую матрицу, требует вызова matrix_free

   * Единичная квадратная матрица (аналогично, только квадратная матрица)

   * Копирование (клонирование)

      struct matrix * matrix_clone (const struct matrix *m);

      возвращает новую матрицу, требует вызова matrix_free

      struct matrix * matrix_assign (struct matrix *m1, const struct matrix *m2);
      возвращает m1 или NULL, если присваивание невозможно (размеры не совпадают) - хотя можно в этом случае менять размер (нельзя делать return matrix_clone(m2), т.к. вызов этой функции не должен требовать доп. вызова matrix_free для возвращаемой матрицы).


Следующие задачи должны быть реализованы через функции доступа по индексу, без реального доступа к полям (быть независимыми от представления в памяти)
*/

//
matrixLine *matrixLine_set_zero(matrixLine *m)
{
    double *ptr = m->mat, *ptrEnd = m->mat + m->vert*m->hor;
    for(; ptr < ptrEnd; ++ptr)
    {
        *ptr = 0;
    }
    return m;
}

matrixLine *matrixLine_identity(matrixLine *m)
{
    if(m->vert != m->hor) return NULL;
    double *ptr = m->mat, *end = m->mat + m->vert*m->hor;
    size_t shift = m->hor + 1;
    for(; ptr < end; ++ptr)
    {
        if((ptr - m->mat) % shift == 0)
        {
            *ptr = 1;
        } else *ptr = 0;
    }
    return m;
}

matrixLine *matrixLine_assign(matrixLine *m, const matrixLine *m1)
{
    if(m->hor != m1-> hor || m->vert != m1->vert) return NULL;
    const double *ptr = (const double *)m1->mat, *ptrEnd = (const double *)m1->mat + m1->vert*m1->hor;
    double *ptrM = m->mat;
    while(ptr < ptrEnd)
    {
        *(ptrM++) = *(ptr++);
    }
    return m;
}

void matrixLine_scan(matrixLine *m)
{
    size_t j = m->vert*m->hor;
    for(size_t i = 0; i < j; ++i)
        scanf("%lf", &m->mat[i]);
}

void matrixLine_copy(matrixLine *m, double *md, size_t n)
{
    if(m && md && (m->hor*m->vert == n))
    {
        m->mat = md;
        matrixLine_print(m);
    }

}

void matrixLine_print(matrixLine *m)
{
    size_t j = m->vert*m->hor;
    for(size_t i = 0; i < j; ++i)
    {
        if(i % m->hor == 0)
        {
            printf("\n");
        }
        printf("%lf\t", m->mat[i]);
    }
}

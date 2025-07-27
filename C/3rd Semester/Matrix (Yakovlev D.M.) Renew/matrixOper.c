#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include"matrixStruct.h"
#include"matrixInitFunc.h"

/**
3. Матричные операции
   * Арифметические: сложение, вычитание, умножение на скаляр, умножение двух матриц

     вариант с записью в третью матрицу (не обязательно, можно через присваивание и арифметическое присваивание)
     struct matrix * matrix_sum (struct matrix *m, const struct matrix *m1, const struct matrix *m2);
     возвращает m = m1+m2 или NULL, если суммирование невозможно (матрицы разных размеров)

     struct matrix * matrix_add (struct matrix *m1, const struct matrix *m2);
     выполняет m1 += m2, возвращает m2 или NULL, если сложение невозможно

     внимание для произведения: для *= нужна промежуточная матрица (и изменение размера для неквадратных матриц), для * нужно следить, чтобы m не совпадал ни с m1,  ни m2 (сам указатель).

   * Транспонирование: прямоугольной матрицы, квадратной матрицы "на месте"

   * Операции со строками
      умножение строки матрицы на число
      сложение двух строк
      перестановка строк
      (не обязательно, для большей эффективности метода Гаусса: выделение строки в другую матрицу 1*n - присваивание, без выделения памяти, прибавление к строке матрицы другой матрицы 1*n и т.п.)
*/

//Line

matrixLine *matrixLine_sum(matrixLine *m, const matrixLine *m1, const matrixLine *m2)
{
    if(m->hor != m1->hor || m->hor != m2->hor || m->vert != m1->vert || m->vert != m2->vert) return NULL;
    if(!m || !m1 || !m2) return NULL;
    double *ptrM = m->mat, *ptrMEnd = m->mat + m->vert*m->hor;
    const double *ptrM1 = (const double *) m1->mat, *ptrM2 = (const double *) m2->mat;
    for(; ptrM < ptrMEnd; ++ptrM, ++ptrM1, ++ptrM2)
    {
        *ptrM = *ptrM1 + *ptrM2;
    }
    return m;
}

matrixLine *matrixLine_mult_scalar_row(matrixLine *m, size_t i, double eps)
{
    if(!m || i >= m->vert || eps == 0) return NULL;
    double *ptr = m->mat + i*m->hor, *ptrEnd = m->mat + (i + 1)*m->hor;
    for(; ptr < ptrEnd; ++ptr)
    {
        *ptr *= eps;
    }
    return m;
}

matrixLine *matrixLine_mult_scalar_column(matrixLine *m, size_t j, double eps)
{
    if(!m || j >= m->hor || eps == 0) return NULL;
    double *ptr = m->mat, *ptrEnd = m->mat + m->vert;
    for(; ptr < ptrEnd; ++ptr)
    {
        *(m->mat + (ptr - m->mat)*m->hor + j) *= eps;
    }
    return m;
}

matrixLine *matrixLine_mult_scalar_all(matrixLine *m, double eps)
{
    if(!m || eps == 0) return NULL;
    double *ptr = m->mat, *ptrEnd = m->mat + m->vert*m->hor;
    for(; ptr < ptrEnd; ++ptr)
    {
        *ptr *= eps;
    }
    return m;
}

matrixLine *matrixLine_substr(matrixLine *m, const matrixLine *m1, const matrixLine *m2)
{
    if(m->hor != m1->hor || m->hor != m2->hor || m->vert != m1->vert || m->vert != m2->vert) return NULL;
    if(!m || !m1 || !m2) return NULL;
    double *ptr = m->mat, *ptrEnd = m->mat + m->vert*m->hor;
    const double *ptrM1 = (const double *) m1->mat, *ptrM2 = (const double *) m2->mat;
    for(; ptr < ptrEnd; ++ptr, ++ptrM1, ++ptrM2)
    {
        *ptr = *ptrM1 - *ptrM2;
    }
    return m;
}

matrixLine *matrixLine_mult_matrixes(const matrixLine *m1, const matrixLine *m2)
{
    if(!m1 || !m2) return NULL;
    matrixLine *m = matrixLine_alloc(m1->vert, m2->hor);
    matrixLine_set_zero(m);
    double *ptr = m->mat, *ptrEnd = m->mat + m->vert;
    const double *ptrM1 = (const double *) m1->mat;
    for(; ptr < ptrEnd; ++ptr, ++ptrM1)
    {
        double *ptrRow = m->mat + (ptr - m->mat)*m->hor, *ptrRowEnd = m->mat + (ptr - m->mat + 1)*m->hor;
        const double *ptrM2 = (const double *) m2->mat;
        for(; ptrRow < ptrRowEnd; ++ptrRow, ++ptrM2)
        {
            const double *ptrM1Row = (const double *) m1->mat + (ptrM1 - m1->mat)*m1->hor;
            const double *ptrM1RowEnd = (const double *) m1->mat + (ptrM1 - m1->mat + 1)*m1->hor;
            for(; ptrM1Row < ptrM1RowEnd; ++ptrM1Row)
            {
                //printf("\n*ptrRow = %lf\n", *ptrRow);
                double p = *(ptrM2 + ((ptrM1Row - m1->mat) % m1->hor)*m2->hor);
                *ptrRow += *ptrM1Row*p;
                //printf("*ptrRow = %lf\n*ptrM1Row = %lf\nm = %lf\n", *ptrRow, *ptrM1Row, p);
                //int d;
                //scanf("%d", &d);
            }
        }
    }
    return m;
}

matrixLine *matrixLine_mult_matrixes_Taylor(const matrixLine *m1, const matrixLine *m2)
{
    if(!m1 || !m2) return NULL;
    matrixLine *m = matrixLine_alloc(m1->vert, m2->hor);
    matrixLine_set_zero(m);
    double *ptr = m->mat, *ptrEnd = m->mat + m->vert;
    const double *ptrM1 = (const double *) m1->mat;
    for(; ptr < ptrEnd; ++ptr, ++ptrM1)
    {
        double *ptrRow = m->mat + (ptr - m->mat)*m->hor, *ptrRowEnd = m->mat + (ptr - m->mat + 1)*m->hor;
        const double *ptrM2 = (const double *) m2->mat;
        for(; ptrRow < ptrRowEnd; ++ptrRow, ++ptrM2)
        {
            const double *ptrM1Row = (const double *) m1->mat + (ptrM1 - m1->mat)*m1->hor;
            const double *ptrM1RowEnd = (const double *) m1->mat + (ptrM1 - m1->mat + 1)*m1->hor;
            for(; ptrM1Row < ptrM1RowEnd; ++ptrM1Row)
            {
                //printf("\n*ptrRow = %lf\n", *ptrRow);
                double p = *(ptrM2 + ((ptrM1Row - m1->mat) % m1->hor)*m2->hor);
                *ptrRow += *ptrM1Row*p;
                //printf("*ptrRow = %lf\n*ptrM1Row = %lf\nm = %lf\n", *ptrRow, *ptrM1Row, p);
                //int d;
                //scanf("%d", &d);
            }
        }
    }
    matrixLine_free((matrixLine *) m1);
    return m;
}

matrixLine *matrixLine_add(matrixLine *m, const matrixLine *m1)
{
    if(!m || !m1 || m->hor != m1->hor || m->vert != m1->vert) return NULL;
    double *ptr = m->mat, *ptrEnd = m->mat + m->vert*m->hor;
    const double *ptrM = (const double *) m1->mat;
    for(; ptr < ptrEnd; ++ptr, ++ptrM)
    {
        *ptr += *ptrM;
    }
    return m;
}

matrixLine *matrixLine_add_row_scalar(matrixLine *m, size_t i, size_t j, double eps)
{
    if(!m || i >= m->vert || j >= m->vert || i == j) return NULL;
    double *ptrI = m->mat + i*m->hor, *ptrIEnd = m->mat + (i + 1)*m->hor;
    double *ptrJ = m->mat + j*m->hor;
    for(; ptrI < ptrIEnd; ++ptrI, ++ptrJ)
    {
        *ptrI += *ptrJ*eps;
    }
    return m;
}

matrixLine *matrixLine_swap_row(matrixLine *m, size_t i, size_t j)
{
    if(!m || i >= m->vert || j >= m->vert) return NULL;
    if(i == j) return m;
    double *ptrI = m->mat + i*m->hor, *ptrIEnd = m->mat + (i + 1)*m->hor;
    double *ptrJ = m->mat + j*m->hor;
    for(; ptrI < ptrIEnd; ++ptrI, ++ptrJ)
    {
        double temp = *ptrI;
        *ptrI = *ptrJ;
        *ptrJ = temp;
    }
    return m;
}


matrixLine *matrixLine_transpose_square(matrixLine *m)
{
    if(!m || m->hor != m->vert) return NULL;
    for(size_t i = 0; i < m->vert; ++i)
    {
        for(size_t j = i; j < m->hor; ++j)
        {
            double temp = *(m->mat + i*m->hor + j);
            *(m->mat + i*m->hor + j) = *(m->mat + j*m->hor + i);
            *(m->mat + j*m->hor + i) = temp;
        }
    }
    return m;
}

matrixLine *matrixLine_transpose_rect(matrixLine *m)
{
    if(!m) return NULL;
    if(m->vert == m->hor) return matrixLine_transpose_square(m);
    matrixLine *m1 = matrixLine_alloc(m->hor, m->vert);
    double *ptr = m->mat, *ptrEnd = m->mat + m->vert;
    double *ptrM1 = m1->mat;
    for(; ptr < ptrEnd; ++ptr, ++ptrM1)
    {
        double *ptrRow = m->mat + (ptr - m->mat)*m->hor, *ptrRowEnd = m->mat + (ptr - m->mat + 1)*m->hor;
        for(; ptrRow < ptrRowEnd; ++ptrRow)
        {
            *(ptrM1 + ((ptrRow - m->mat) % m1->vert)*m1->hor) = *ptrRow;
        }

    }
    return m1;
}

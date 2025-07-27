#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>
#include<math.h>
#include"matrixInitFunc.h"
#include"matrixStruct.h"
#include"matrixOper.h"

/**
* �������� �� ��������
      ��������� ������ ������� �� �����
      �������� ���� �����
      ������������ �����
      (�� �����������, ��� ������� ������������� ������ ������: ��������� ������ � ������ ������� 1*n - ������������, ��� ��������� ������, ����������� � ������ ������� ������ ������� 1*n � �.�.)

4. ������ � ���������
   * ����� ������
     - ������� ������� ��������� (����: n*n �������, 1*n ������� ��������� ������, 1*n ������� ��� ������ ����������, �����:  1*n ������� ������� ��� NULL ���� ������� ����������)
     - ��������� ���������� �������

     ��������� �������� ����� ������������ (������������ ����� ��� ����� ����� ������ �������� ������� �����).

    ������� �������������� �������� ���������� � ��������� ��������� eps.


   * ��������� ����� (�������� ����� ������� ��������� ������ �� ���� ������� ��� �������� ����� ������� ��������� �������� �� ���� ��������)

   * ��������� ����������
      exp A = E + A + A^2/2 +...+ A^n/n! +... =  a0 + a1 + ... + an +...

     a0 = E
     an = a_{n-1} * A / n

    ������������ �� ||an|| < eps


    ��� ��������:


      1 0 0        e 0    0
      0 2 0   ->   0 e^2  0
      0 0 -1       0 0    1/e



������ ������� ��������� �� ������ (������ ��� ���������, ��� ��������, ��� ������ ������, ��� ���� � �.�.).

������� �� const.


����� ������� �� ����������� �����, ��� �������, �� ������� ������������ ���������� ������: "���������_����������" ��� ���� ��������������� (����� ��������� �������� ���� ��� ����������� ��������� ������� � ��������� � ����� ���������).

������� - �������� �������� (����� �������� �����).
*/
/**
* ����� ������
     - ������� ������� ��������� (����: n*n �������, 1*n ������� ��������� ������, 1*n ������� ��� ������ ����������, �����:  1*n ������� ������� ��� NULL ���� ������� ����������)
     - ��������� ���������� �������

     ��������� �������� ����� ������������ (������������ ����� ��� ����� ����� ������ �������� ������� �����).

    ������� �������������� �������� ���������� � ��������� ��������� eps.
*/
//Dyn
/*
matrixDyn * matrixDyn_Gauss_Method(matrixDyn *m, matrixDyn *ext)
{
    if(!m || m->vert != m->hor || !ext || ext->vert != m->vert || ext->hor != 1) return NULL;
    matrixDyn *result = matrixDyn_alloc(ext->vert, ext->hor);
    if(!result) return NULL;
    // ������ ��� ������
    // ����: �������� ������ �������� ����� � ������� ���������� ��������
    // ���� ��� ���, ���������� NULL, ���� �� ���� - ������ ������� 0 � i �����
    // ����� ��������� ���������, ����� ���� ������������� ������� n-1 x n-1 � ��������� ��� �� 1 � 1
    for(size_t i = 0; i < m->vert; ++i)
    {
        size_t maxInd = i;
        double cfntMax = *(*(m->mat + i) + i);
        for(size_t j = i; j < m->vert; ++j) // ����� ���������� ��������
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
        // �������� ��� �������� ������� ���� i-��� ��������
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

    // �������� ��� ������
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
    // ������ ��� ������
    // ����: �������� ������ �������� ����� � ������� ���������� ��������
    // ���� ��� ���, ���������� NULL, ���� �� ���� - ������ ������� 0 � i �����
    // ����� ��������� ���������, ����� ���� ������������� ������� n-1 x n-1 � ��������� ��� �� 1 � 1
    printf("\n|| Phase 1 ||\n");
    for(size_t i = 0; i < m->vert; ++i)
    {
        printf("\n|==| i = %Iu |==|\n", i);
        size_t maxInd = i;
        double cfntMax = *(m->mat + i*m->hor + i);
        for(size_t j = i; j < m->vert; ++j) // ����� ���������� ��������
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
        // �������� ��� �������� ������� ���� i-��� ��������
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
    // ��� 0.
    matrixLine *a0 = matrixLine_alloc(m->vert, m->hor); // ����� ������
    matrixLine *a1 = matrixLine_clone(m);
    if(!a0 || !a1) return NULL;
    matrixLine_identity(a0);
    size_t n = 2;
    // ��� 1 � ��� �����.


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

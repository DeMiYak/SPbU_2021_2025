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

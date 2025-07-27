/**
* ������� ����� ���������� (�)
* ���������� "�������� ��������� � �������"
* ����: ������ �� n ���������
* �����: ���������� ������� ������� � ����������� e
*/

#include"head.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<assert.h>


int main()
{
    int k;
    printf("Please, select one of the following by pressing a key:\n1 for a\n 2 for b\n 3 for c\n");
    scanf("%d", &k);
    assert(0 < k && k < 4);
    switch (k)
    {
    case 1:
        /**
        * 14.2 (a)
        * ����� �������� ���������������
        * � ����������� ������ ������������������� ����������
        */

        size_t n;
        scanf("%Iu", &n);
        double *a, *sum = 0;
        a = malloc(sizeof(double)*n);
        assignDbl(n, a, &sum);
        // ���������� �������� ��������������� mar � ����. ������ msq
        double *mar, *msq;
        analyseArray(n, a, &mar, &msq, &sum);
        // ����� ��������� �������
        printArDbl(n, a);
        printf("\nmar = %lf\nmsq = %lf", mar, msq);
        free(a);
        break;

    case 2:
        /**
        * 14.2(b)
        * ����� ��������� �� ������ ������� �' ������� �������,
        * �������������� �� ��������� �������� � �����, ��� �� �,
        * ������� � ��������� �������� �
        */
        size_t n;
        scanf("%Iu", &n);
        //
        double *c, *sum = 0;
        c = malloc(sizeof(double)*n);
        assignDbl(n, c, &sum);
        //
        double *mar, *msq;
        analyseArray(n, c, &mar, &msq, &sum);
        //
        double a, eps, *xf;
        size_t k;
        //
        printf("\na = ");
        scanf("%lf", &a);
        //
        printf("\neps = ");
        scanf("%lf", &eps);
        //
        printf("\nk = ");
        scanf("%ld", &k);
        //
        assert(k < n);
        //
        xf = pointValue(n, c, a, eps, k);
        if(xf != NULL) printf("%lf\n", *xf);
        //
        printArDbl(n, c)
        free(c);
        break;

    case 3:
        /**
        * 14.2(c)
        * ����� ���� "��������" � �������
        */

        size_t n;
        scanf("%Iu", &n);
        double *a, *sum = 0;
        a = malloc(sizeof(double)*n);
        assignDbl(n, a, &sum);
        //
        double *mar, *msq;
        analyseArray(n, a, &mar, &msq, &sum);
        missAr(n, a, &mar, &msq);
        printf("\n");
        //
        printArDbl(n, a);
        break;
    }
    return 0;
}

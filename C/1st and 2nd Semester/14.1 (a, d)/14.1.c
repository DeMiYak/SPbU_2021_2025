/**
* ������� ����� ���������� (�)
* ������� ��������� � ������� ���������� �������� ����������� ���������� ����������
* ����: ������ � � n ����������
* �����: �������� ��������������� ����������� ���������� ����������
*/

/**
* 14.1(a)
* ���� � ���������� � ����� �� ����� ��������
* ����� � ������������ ����� �������� ������������� �����

#include<stdio.h>
#include"head.h"
#include<stdlib.h>

int main()
{
    size_t n;
    scanf("%Iu", &n);
    double *a;
    a = malloc(sizeof(double)*n);
    //
    assigndbl(n, a);
    //
    printardbl(n, a);
    //
    free(a);
}
*/


/**
* 14.1 (d)
* �������� ���� ������ ��� �������� ��������� �� ������� ����� �����
*/

#include<stdio.h>
#include"head.h"
#include<stdlib.h>

int main()
{
    size_t n;
    scanf("%Iu", &n);
    int *a;
    a = malloc(sizeof(int)*n);
    assignint(n, a);
    //
    size_t k = pickeven(n, a);
    printarint(k, a);
    free(a);
}

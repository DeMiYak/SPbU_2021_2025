/**
* ������� ����� ���������� (�)
* ���������� ������� �� �������� �������� ������� (�� ��������)
* ����: ����� ������� i, ������������� �������� a
* �����: k - ������ �� �������� �����
* (���� max1 ��� max2 ������������ - ��������� 0)
*/


#include<stdio.h>
#include"QQ.h"

int main()
{
    size_t n;
    printf("Set the length of the x-array: ");
    scanf("%d", &n);
    int x[n];
    arrayint(x, n);
    printf("%d", arrayintcountk(x, n));
}

// +

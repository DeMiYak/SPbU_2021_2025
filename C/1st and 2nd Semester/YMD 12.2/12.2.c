/**
* ������� ����� ���������� (�)
* ����������� ����� ��������� ����� ���������
* � ������� ��������� ������������� ��������
* ����: ����� ������� i, ������������� �������� a
* �����: k - ����� ������������
*/


#include<stdio.h>
#include"sip.h"

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

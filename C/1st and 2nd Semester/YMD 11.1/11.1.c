/**
* ������� ����� ���������� (�)
* ���������� ��� � ���
* ������� ������: � � b - ������������ ����������� �����
* �����: ��� � ���
*/


#include<stdio.h>
#include<math.h>
#include"support.h"

int main()
{
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d\n%d\n%d", iterEuclid(a, b), recuEuclid(a, b), NOK(a, b));
    return 0;
}

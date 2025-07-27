/**
* ������� �.�. (�)
* ���������� ����� ���� ����� � ���������� ���� � �-����� ������� ���������
* ����: ����� n, ������� ��������� �.
* �����: ���-�� ���� � � �� ����� sum.
*/

#include<stdio.h>

void summa(int number, int p, int *c, int *sum){
    *sum = 0;
    *c = 0;
    while(number){
        *sum += number%p;
        number /= p;
        ++*c;
    }
}

int main()
{
    int n, p, c, sum;
    scanf("%d%d", &n, &p);
    summa(n, p, &c, &sum);
    printf("%d, %d, %d, %d", n, p, c, sum);
}

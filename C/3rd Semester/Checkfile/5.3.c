/**
* ����� � ������ �������� �� 1 �� 99
* ������� ������: ���-�� ������ (�� 1 �� 99)
* �����: ���-�� ������ (�������)
*/

#include<stdio.h>
#include<locale.h>
#include<assert.h>

void rubles(int d){
    switch(d%10){
        case 1:
            printf("���� �����");
            break;
        case 2:
            printf("��� �����");
            break;
        case 3:
            printf("��� �����");
            break;
        case 4:
            printf("������ �����");
            break;
        case 5:
            printf("���� ������");
            break;
        case 6:
            printf("����� ������");
            break;
        case 7:
            printf("���� ������");
            break;
        case 8:
            printf("������ ������");
            break;
        case 9:
            printf("������ ������");
            break;
        default:
            printf("������");
            break;
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    int n;
    scanf("%d", &n);
    assert(n>0 && n<100);
    switch(n/10){
        case 1:
            switch(n%10){
                case 1:
                    printf("����������� ������");
                    break;
                case 2:
                    printf("���������� ������");
                    break;
                case 3:
                    printf("���������� ������");
                    break;
                case 4:
                    printf("������������ ������");
                    break;
                case 5:
                    printf("���������� ������");
                    break;
                case 6:
                    printf("����������� ������");
                    break;
                case 7:
                    printf("���������� ������");
                    break;
                case 8:
                    printf("������������ ������");
                    break;
                case 9:
                    printf("������������ ������");
                    break;
                default:
                    printf("������ ������");
                    break;
            }
            break;
        case 2:
            printf("�������� ");
            break;
        case 3:
            printf("�������� ");
            break;
        case 4:
            printf("����� ");
            break;
        case 5:
            printf("��������� ");
            break;
        case 6:
            printf("���������� ");
            break;
        case 7:
            printf("��������� ");
            break;
        case 8:
            printf("����������� ");
            break;
        case 9:
            printf("��������� ");
            break;
    }
    if(n/10 != 1){
        rubles(n);
        }
}

/**
* ������� ����� ���������� (�)
* ������� ���������� �� ������ (��� � �����) ��������
* ����: ������, �� ����������� ������� �������� ��������
* �����: ������, ���������� ����� ������� � ������� ���������� ���� ������
*/
#include<stdio.h>
#include"head.h"
#include<stdlib.h>

int main()
{
    size_t limit;
    printf("limit = ");
    scanf("%Iu\n", &limit);
    char temp;
    scanf("%c", &temp);
    printf("%i %c\n", temp, temp);
    char *src = malloc(sizeof(char)*limit);
    src[0]=' ';
    src++;
    arrFill(src, limit);
    removeSpace(src);
    printf("2");
    printf("|%s|", src);
    free(src--);
    return 0;
}

/**
* ����������� - ����������� � ������ ������� �������
*/

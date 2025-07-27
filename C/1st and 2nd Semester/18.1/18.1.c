/**
* ������� ����� ���������� (�)
* ���� ������ ���� ��������, ����� �����������
* ��������� � ������� ����������. ����������� ����� �����������,
* ����� ����������� � ������ � ����� ������. ������������� ������ � ������ ����.
* ����������: ������� ����� ������ � ������, � ���, ��������� ������� strtok,
* �������� ����� ���������� �����, ������� ����������� �������� � ����� 0,
* ��������� � ������� ���������� �� char ������ ���������� �����
* ����: ������ ��������, ���������� ��������� ��� ������� ����������
* �����: ������ ����
*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"head.h"

int main()
{
    size_t limit;
    printf("limit = ");
    scanf("%Iu", &limit);
    char temp;
    scanf("%c", &temp);
    // printf("%i %c\n", temp, temp);
    // �������� � ���������� ������� ��������
    char *src = malloc(sizeof(char)*limit);
    // ��������� ������ ��� ������������ ��������� ������
    char **cpy = (char **) malloc(sizeof(char *)*limit);
    for(size_t i = 0; i < limit; ++i)
    {
        cpy[i] = (char *) malloc(sizeof(char *)*limit);
    }
    arrFill(src, limit);
    //

    // ����� ������� � ����� ������� ����
    size_t n = transferArr(src, cpy);
    for(char **ptr = cpy; n > 0; ++ptr, --n) printf("|%s|\n", *ptr);
    //
    free(src);
    for(size_t i = 0; i < limit; ++i) free(cpy[i]);
    free(cpy);
}

/**
* ������� ����� ���������� (�)
* ���� ������ ���� �������� � �������������.
* ����� ������� ������������� � ����� ��������� ����
* ����: ������ ���� ��������
* �����: ������ ���� � ����� ���������� ��� ������� ����� n - ����� ���������, f - ������� �������������
*/

#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>
#include<string.h>
#include"head.h"

int main()
{
    // 0. ��������� ������ ��� ������������ ��������
    size_t limit;
    printf("limit = ");
    scanf("%Iu", &limit);
    char *src = malloc(limit);
    char **cpy = (char **) malloc(sizeof(char *)*limit);
    // 1. ���������� �������
    char temp;
    scanf("%c", &temp);
    // printf("%i\n", temp);
    arrFill(src, limit);
    size_t n = transferArr(src, cpy);
    // 2. �������� � ���������� ������ ����
    for(char **ptr = cpy; *ptr != NULL ; ++ptr)
        printf("%p %s\n", ptr, *ptr);
    node *data = createMap(cpy);
    printStr(data, &n);
    free(src);
    free(cpy);
}

/**
* ����������� ����������� �������� �������� ������ �����������
* �����. �� ���� ������ ��������� ������. �� ����� - ���������
* ��� ��������� �� ������. ������������ ����� � ��������� �������.

* �������� �������������� ��������: ��������, ���������, ���������, �������, ���������� � �������
* �������������� �������
* ���������
* �� ���� �����: ������� �������������� n �����, *����������� ��������
*/

#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include<string.h>
#include"stack.h"
#include"revPolNot.h"

int main()
{
    size_t len = 1000;
    stack *st = stack_alloc();
    char com[100];
    while (strcmp(com, "end") != 0) {
        scanf("%s", com);
        double tempI;
        if (sscanf(com, "%lf", &tempI) == 1) {
            stack_insert(st, tempI);
        } else {
            if (revPolNot(st, com) == 0)
                stack_to_str(st, NULL, len);
            else
                printf("error\n");
        }
    }
}

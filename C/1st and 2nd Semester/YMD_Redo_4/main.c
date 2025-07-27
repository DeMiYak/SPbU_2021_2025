/**
* Яковлев Денис Михайлович (С)
* Найти номер строки, содержащей первое вхождение
* в файл заданного числа (если нет - вернуть 0)
*/

#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>
#include"read.h"

// +
int main()
{
    int key;
    printf("Enter key = ");
    scanf("%d", &key);
    size_t line = strnum("int.txt", key);
    printf("Line = %Iu", line);
    return 0;
}

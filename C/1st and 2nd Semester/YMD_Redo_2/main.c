/**
* Яковлев Денис Михайлович (С)
* Найти кол-во слов, начинающихся с заданной буквы
*/
#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>
#include"read.h"

int main()
{
    printf("Enter line: ");
    char *line = writeLine();
    char key;
    printf("Key = ");
    scanf("%c", &key);
    size_t count = readLine(line, key);
    printf("\n\nCount = %Iu\nLine = %s\n", count, line);
    printf("\nCleaning line...\n");
    free(line);
    printf("\nCleaning complete...\n");
    return 0;
}

// today is a good day to fry, isn't it?

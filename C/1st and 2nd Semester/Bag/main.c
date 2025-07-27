#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>
#include"help.h"

int main()
{
    printf("Enter the line: ");
    char *line = writeLine();
    char letter;
    size_t number = 0;
    printf("letter = ");
    scanf("%c", &letter);
    number = readLine(line, letter);
    printf("number = %Iu", number);
    free(line);
    return 0;
}

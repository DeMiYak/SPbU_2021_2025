#include<stdio.h>
#include<stdlib.h>
#include"sup.h"

int main()
{
    size_t len, count, ren;
    printf("length = ");
    scanf("%Iu", &len);

    {
        char temp;
        scanf("%c", &temp);
        printf("\n%c, %i\n", temp, temp);
    }

    char letter;
    printf("letter = ");
    scanf("%c", &letter);
    printf("%c, %i\n", letter, letter);

    {
        char temp;
        scanf("%c", &temp);
        printf("\n%c, %i\n", temp, temp);
    }

    char *src = malloc(sizeof(char)*len);

    ren = arrFill(src, len);
    count = findc(src, ren, letter);
    printf("\ncount = %Iu\nren = %Iu", count, ren);
    free(src);
    return 0;
}

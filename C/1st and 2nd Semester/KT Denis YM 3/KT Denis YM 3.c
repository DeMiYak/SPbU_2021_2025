#include<stdio.h>
#include"save.h"

int main()
{
    double a, b, c;
    scanf("%lf%lf%lf", &a, &b, &c);
    switch (CheckTriangle(a, b, c))
    {
    case(STRAIGHT):
        printf("STRAIGHT");
        break;
    case(BLUNT):
        printf("BLUNT");
        break;
    case(SHARP):
        printf("SHARP");
        break;
    case(RIGHT):
        printf("RIGHT");
        break;
    default:
        printf("NONEXISTENT");
        break;
    }

    return 0;
}

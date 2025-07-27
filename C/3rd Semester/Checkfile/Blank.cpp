#include<iostream>
#include<stdio.h>
#include<stdlib.h>

int main()
{
    int n, minutes, seconds
    scanf("i%", n);
    minutes = n/60%60;
    seconds = n/1%60;
    printf("The time is:");
    printf("minutes = %i", minutes);
    printf(":");
    printf("seconds = %i", seconds);
    return 0;
}

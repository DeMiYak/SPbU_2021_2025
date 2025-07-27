#include<stdio.h>
#include"head.h"

void removeSpace(char *string)
{
    char *ptrWrite = string;
    for(char *ptrRead = string; *ptrRead != '\0'; ++ptrRead){
        while(*ptrRead == ' ' && *(ptrRead + 1) == ' '){
            ++ptrRead;
        }
        *ptrWrite = *ptrRead;
        ++ptrWrite;
    }
    *ptrWrite = '\0';
}


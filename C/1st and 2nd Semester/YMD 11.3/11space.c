#include<stdio.h>

void issue(int a){
    switch (a)
    {
    case 10:
        printf("A");
        break;
    case 11:
        printf("B");
        break;
    case 12:
        printf("C");
        break;
    case 13:
        printf("D");
        break;
    case 14:
        printf("E");
        break;
    case 15:
        printf("F");
        break;
    default:
        printf("%d", a);
        break;
    }

}

void iterReverseNum (int a, int p){
    while(a != 0){
        int c = a%p;
        issue(c);
        a /= p;
    }
}


void recurNum (int a, int p){
    int c = a%p;
    if (a / p != 0) recurNum(a/p, p);
    issue(c);
}

void recurReverseNum (int a, int p){
    int c = a%p;
    issue(c);
    a /= p;
    return a == 0 ? "" : recurReverseNum(a, p);
}

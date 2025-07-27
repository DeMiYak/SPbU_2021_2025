/**
* ¬ывод в рубл€х значений от 1 до 99
* ¬водные данные: кол-во рублей (от 1 до 99)
* ¬ывод: кол-во рублей (словами)
*/

#include<stdio.h>
#include<locale.h>
#include<assert.h>

void rubles(int d){
    switch(d%10){
        case 1:
            printf("один рубль");
            break;
        case 2:
            printf("два рубл€");
            break;
        case 3:
            printf("три рубл€");
            break;
        case 4:
            printf("четыре рубл€");
            break;
        case 5:
            printf("п€ть рублей");
            break;
        case 6:
            printf("шесть рублей");
            break;
        case 7:
            printf("семь рублей");
            break;
        case 8:
            printf("восемь рублей");
            break;
        case 9:
            printf("дев€ть рублей");
            break;
        default:
            printf("рублей");
            break;
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    int n;
    scanf("%d", &n);
    assert(n>0 && n<100);
    switch(n/10){
        case 1:
            switch(n%10){
                case 1:
                    printf("одиннадцать рублей");
                    break;
                case 2:
                    printf("двенадцать рублей");
                    break;
                case 3:
                    printf("тринадцать рублей");
                    break;
                case 4:
                    printf("четырнадцать рублей");
                    break;
                case 5:
                    printf("п€тнадцать рублей");
                    break;
                case 6:
                    printf("шестнадцать рублей");
                    break;
                case 7:
                    printf("семнадцать рублей");
                    break;
                case 8:
                    printf("восемнадцать рублей");
                    break;
                case 9:
                    printf("дев€тнадцать рублей");
                    break;
                default:
                    printf("дес€ть рублей");
                    break;
            }
            break;
        case 2:
            printf("двадцать ");
            break;
        case 3:
            printf("тридцать ");
            break;
        case 4:
            printf("сорок ");
            break;
        case 5:
            printf("п€тьдес€т ");
            break;
        case 6:
            printf("шестьдес€т ");
            break;
        case 7:
            printf("семьдес€т ");
            break;
        case 8:
            printf("восемьдес€т ");
            break;
        case 9:
            printf("дев€носто ");
            break;
    }
    if(n/10 != 1){
        rubles(n);
        }
}

#include <stdio.h>
#include <assert.h>
#include <locale.h>

void printRub(int n) {
    switch (n % 10) {
        case 0:
            printf(" рублей");
        case 1:
            printf(" один рубль");
        case 2:
            printf(" два рубля");
        case 3:
            printf(" три рубля");
        case 4:
            printf(" четыре рубля");
        case 5:
            printf(" пять рублей");
        case 6:
            printf(" шесть рублей");
        case 7:
            printf(" семь рублей");
        case 8:
            printf(" восемь рублей");
        case 9:
            printf(" девять рублей");
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    int n;
    scanf("%i", &n);
    assert(n > 0 && n < 100);
    switch (n / 10) {
        case 1:
            switch (n % 10) {
                case 0:
                    printf("десять");
                case 1:
                    printf("одинадцать");
                case 2:
                    printf("двенадцать");
                case 3:
                    printf("тринадцать");
                case 4:
                    printf("четырнадцать");
                case 5:
                    printf("пятнадцать");
                case 6:
                    printf("шестнадцать");
                case 7:
                    printf("семнадцать");
                case 8:
                    printf("восемнадцать");
                case 9:
                    printf("девятнадцать");
            }
            printf(" рублей");
        case 2:
            printf("двадцать");
        case 3:
            printf("тридцать");
        case 4:
            printf("сорок");
        case 5:
            printf("пятьдесят");
        case 6:
            printf("шестьдесят");
        case 7:
            printf("семьдесят");
        case 8:
            printf("восемьдесят");
        case 9:
            printf("девяносто");
    }
    if (n / 10 != 1)
        printRub(n);
}

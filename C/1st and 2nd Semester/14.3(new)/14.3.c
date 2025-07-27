/**
* Яковлев Денис Михайлович (С)
* Бинарный поиск и место
* Ввод: Массив в виде нетипизированного указателя
* Вывод: Указатель на найденный элемент или NULL, если
* элемента в массиве нет (бинарный поиск);
* Индекс элемента, на котором следует вставить искомый элемент в массив
* с сохранением упорядоченности при условии сдвига (бинарное место).
*/


#include<stdio.h>
#include<stdlib.h>
#include"head.h"


int main()
{
    void* arr;
    size_t length;
    int k;
    printf("length = ");
    scanf("%Iu", &length);
    printf("\nk = ");
    scanf("%d", &k);
    if(k)
    {
        arr = malloc(sizeof(double)*length);
        assignDbl(arr, length);
    }
    else
    {
        arr = malloc(sizeof(int)*length);
        assignInt(arr, length);
    }
    // A
    void* point = binSearch(arr, length, x);
    if(point != NULL) printf("\n14.3(A): point = %p", point);
    //B
    size_t ind = binPlace(arr, length, x);
    printf("\n14.3(B): ind = %Iu", ind);
    return 0;
}

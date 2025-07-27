#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

/**
* Функция бинарного поиска
* Входные данные: массив, элемент сравнения, длина массива, функция сравнения
* Вывод: указатель на найденный элемент, если имеется (в противном случае NULL)
*/
void *BinSearch(void *, void *, size_t, size_t, int (*compare)(const void *, const void *));

/**
* Функция бинарного места
* Входные данные: массив, элемент сравнения, длина массива, функция сравнения
* Вывод: указатель на место, куда поставится элемент сравнения в упорядоченном массиве
*/
void *BinPlace(void *, void *, size_t, size_t, int (*compare)(const void *, const void *));


void arrFill(int *, size_t);

#endif // HEAD_H_INCLUDED

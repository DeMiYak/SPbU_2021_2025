#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>
#include<string.h>
#include"head24.h"
#include"sort.h"

/**
* a) добавление элемента
* b) удаление элемента (по номеру)
* c) сортировка массива (по выбранному полю; по возрастанию; по убыванию)
* d) вывод элементов массива на экран и в текстовый файл
* e) прочтение массива из текстового файла
* f) вывод столбчатой диаграммы по выбранному полю с легендой
* g) вывод круговой диаграммы по выбранному полю с легендой
*/

// 0 +
void strScan(char *letter)
{
    {
        char temp;
        scanf("%c", &temp);
    }
    char *ptr = letter, *ptrEnd = letter + 100;
    for(; ptr < ptrEnd; ++ptr)
    {
        scanf("%c", ptr);
        if(*ptr == '\n') break;
    }
    *ptr = '\0';
}

// Чтение слова до ввода каретки
char *strCpy()
{
    size_t sizeC = 4;
    char *cTemp = malloc(sizeC);
    if(!cTemp) return NULL;
    char *ptr = cTemp;
    while(*ptr != '\n')
    {
        if(sizeC == (ptr - cTemp))
        {
            sizeC *= 2;
            cTemp = realloc(cTemp, sizeC);
        }
        scanf("%c", ptr);
        ++ptr;
    }
    *ptr = '\0';
    return cTemp;
}
//

data *data_base_alloc(data *d)
{
    if(!d) return NULL;
    d->len = 0;
    d->arrSize = 4;
    d->p = malloc(sizeof(base)*d->arrSize);
    return d;
}

data *data_alloc()
{
    data *d = malloc(sizeof(data));
    if(!d) return NULL;
    d->len = 0;
    d->arrSize = 4;
    d->p = malloc(sizeof(base)*d->arrSize);
    return d;
}

void data_free(data *d)
{
    free(d->p);
    free(d);
}
//


// A +
data *data_insert(data *d, char *initials, int age, double weight)
{
    if(!d) return NULL;
    if(!d->p)
    {
        data_base_alloc(d);
        d->len++;
        d->p[d->len - 1].age = age;
        d->p[d->len - 1].initials = initials;
        d->p[d->len - 1].weight = weight;
        return d;
    }
    if(++d->len > d->arrSize)
    {
        d->arrSize *= 2;
        d->p = realloc(d->p, d->arrSize*sizeof(base));
        d->p[d->len - 1].age = age;
        d->p[d->len - 1].initials = initials;
        d->p[d->len - 1].weight = weight;
    }
    else
    {
        d->p[d->len - 1].age = age;
        d->p[d->len - 1].initials = initials;
        d->p[d->len - 1].weight = weight;
    }
    return d;
}
//

// B +
data *data_delete(data *d, size_t i)
{
    if(!d) return NULL;
    if(!d->p) return d;
    if (i >= d->len)
    {
        printf("Error: invalid element\n(Returning the structure)\n");
        return d;
    }
    else
    {
        for(size_t j = i + 1; j < d->len; ++j)
        {
            d->p[j - 1] = d->p[j];
        }
        d->p[d->len - 1].age = 0;
        d->p[d->len - 1].initials = NULL;
        d->p[d->len - 1].weight = 0;
    }
    d->len--;
    return d;
}
//

// C +-
int cmp_by_age(const base *a, const base *b)
{
    return a->age - b->age;
}

int cmp_by_age_inv(const base *a, const base *b)
{
    return -cmp_by_age(a, b);
}

int cmp_by_weight(const base *a, const base *b)
{
    double cmp = a->weight - b->weight;
    if(cmp > 0) return 1;
    if(cmp == 0) return 0;
    return -1;
}

int cmp_by_weight_inv(const base *a, const base *b)
{
    return -cmp_by_weight(a, b);
}

int cmp_by_char(const base *a, const base *b)
{
    return strcmp(a->initials, b->initials);
}

int cmp_by_char_inv(const base *a, const base *b)
{
    return -strcmp(a->initials, b->initials);
}

data *data_sort_age_ascending(data *d)
{
    if(!d) return NULL;
    if(!d->len)
    {
        printf("Error: no elements to sort\n(Returning the structure)\n");
        return d;
    }
    else
    {
        printf("Debug");
        size_t temp = d->len;
        data_sort_quick(d->p, temp, cmp_by_age);
    }
    return d;
}

data *data_sort_age_descending(data *d)
{
    if(!d) return NULL;
    if(!d->len)
    {
        printf("Error: no elements to sort\n(Returning the structure)\n");
        return d;
    }
    else
    {
        printf("Debug");
        size_t temp = d->len;
        data_sort_quick(d->p, temp, cmp_by_age_inv);
    }
    return d;
}

data *data_sort_weight_ascending(data *d)
{
    if(!d) return NULL;
    if(!d->len)
    {
        printf("Error: no elements to sort\n(Returning the structure)\n");
        return d;
    }
    else
    {
        printf("Debug");
        size_t temp = d->len;
        data_sort_quick(d->p, temp, cmp_by_weight);
    }
    return d;
}

data *data_sort_weight_descending(data *d)
{
    if(!d) return NULL;
    if(!d->len)
    {
        printf("Error: no elements to sort\n(Returning the structure)\n");
        return d;
    }
    else
    {
        printf("Debug");
        size_t temp = d->len;
        data_sort_quick(d->p, temp, cmp_by_weight_inv);
    }
    return d;
}

data *data_sort_char_ascending(data *d)
{
    if(!d) return NULL;
    if(!d->len)
    {
        printf("Error: no elements to sort\n(Returning the structure)\n");
        return d;
    }
    else
    {
        printf("Debug");
        size_t temp = d->len;
        data_sort_quick(d->p, temp, cmp_by_char);
    }
    return d;
}

data *data_sort_char_descending(data *d)
{
    if(!d) return NULL;
    if(!d->len)
    {
        printf("Error: no elements to sort\n(Returning the structure)\n");
        return d;
    }
    else
    {
        printf("Debug");
        size_t temp = d->len;
        data_sort_quick(d->p, temp, cmp_by_char_inv);
    }
    return d;
}
//

// D +
void data_print(data *d)
{
    if(d)
    {
        printf("\nNumber\t|\tInitials\t|\tAge\t|\tWeight\t|\t\n");
        for(size_t i = 0; i < d->len; ++i)
        {
            printf("%Iu\t|\t%s\t\t|\t%d\t|\t%lf|\n", i, d->p[i].initials, d->p[i].age, d->p[i].weight);
        }
        printf("\n\nLength = %Iu\narrSize = %Iu", d->len, d->arrSize);
    }
    else
    {
        printf("Data is empty");
    }
}

void data_rewrite_FILE(data *d, char *file)
{
    if(d)
    {
        if(!d->p)
        {
            printf("\nError: no elements to put\n(Returning the structure)\n");
        }
        else
        {
            FILE *f = fopen(file, "w");
            for(size_t i = 0; i < d->len; ++i)
            {
                fprintf(f, "%s %d %lf\n", d->p[i].initials, d->p[i].age, d->p[i].weight);
            }
            fclose(f);
        }
    }
}

//

// E +

data *data_read_FILE(data *d, char *file)
{
    if(!d) return NULL;
    if(!d->p)
    {
        d = data_base_alloc(d);
    }
    FILE *f = fopen(file, "r");
    if(!f)
    {
        printf("\nError: empty file\n(Returning the structure)\n");
        return d;
    }
    while(!feof(f))
    {
        char *initials = malloc(sizeof(char)*100);
        int age;
        double weight;
        fscanf(f, "%s%d%lf", initials, &age, &weight);
        data_insert(d, initials, age, weight);
    }
    data_delete(d, d->len - 1);
    return d;
}

//

// E
/*
friend * fill_DB_from_file(friend * frnds_DB, char *path, size_t *n){

    if(!frnds_DB || !path)return NULL;

    FILE *f;
    char nname[S];
    int nc_frnds;
    double ncash;

    f = fopen(path, "r");

    if(!f)return NULL;


    while(!feof(f)){
        fscanf(f,"%s%d%lf", nname, &nc_frnds, &ncash);
        add_friend(frnds_DB, n, nname, nc_frnds, ncash);
    }

    fclose(f);

    return frnds_DB;
}
*/
//
// F
data *data_pie_diagramm()
{
    return NULL;
}
//

// G
data *data_column_diagramm()
{
    return NULL;
}
//
/*

Идея: создать шесть функций компаратора (сравнителя)
(можно использовать встроенный сортировщик)
Использовать массив значений base *, а не массив указателей

*/

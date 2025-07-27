#ifndef HEAD24_H_INCLUDED
#define HEAD24_H_INCLUDED

typedef struct base
{
    char *initials;
    int age;
    double weight;
}base;

typedef struct data
{
    base *p;
    size_t len, arrSize;
}data;

void strScan(char *letter);

char *strCpy();

data *data_base_alloc(data *d);

data *data_alloc();

data *data_insert(data *d, char *initials, int age, double weight);

data *data_delete(data *d, size_t i);

int cmp_by_age(const base *a, const base *b);

int cmp_by_age_inv(const base *a, const base *b);

int cmp_by_weight(const base *a, const base *b);

int cmp_by_weight_inv(const base *a, const base *b);

int cmp_by_char(const base *a, const base *b);

int cmp_by_char_inv(const base *a, const base *b);

data *data_sort_age_ascending(data *d);

data *data_sort_age_descending(data *d);

data *data_sort_weight_ascending(data *d);

data *data_sort_weight_descending(data *d);

data *data_sort_char_ascending(data *d);

data *data_sort_char_descending(data *d);

void data_print(data *d);

void data_rewrite_FILE(data *d, char *file);

data *data_read_FILE(data *d, char *file);

data *data_pie_diagramm();

data *data_column_diagramm();

void data_free(data *d);

#endif // HEAD24_H_INCLUDED

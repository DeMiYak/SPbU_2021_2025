#ifndef DATA_BASE_H_INCLUDED
#define DATA_BASE_H_INCLUDED

#define N 200
#define S 50
#define PI 3.1415

typedef struct friend {
    size_t num;

    char *name;
    double cash;
    int c_frnds;
} friend;

typedef int (*comp_func) (void *, void *);//compare function

int cmp_c_frnds(void *a, void *b);//compare function for struct friend int: struct friend -> c_frds

int cmp_cash(void *a, void *b);//compare function for struct friend double: struct friend -> cash

int cmp_char(void *a, void *b);//compare function for struct friend char*: struct friend -> char

int cmp_num(void *a, void *b);//compare function for struct friend size_t: struct friend -> num

friend * clone_DB(friend *frnds_DB, size_t * n);//clone friends_DB

friend * init_DB();//initialize Data Base

friend * fill_DB_from_file(friend * frnds_DB, char *path, size_t *n);//fill DB from file with path "path", view of: name | cost | amount of friends|

friend * add_friend(friend * frnds_DB, size_t *n, char *nname, int nc_frnds, double ncash);// add friend in friends_DB

friend * add_friend_cmd(friend * frnds_DB, size_t *n);// add friend in friends_DB in cmd

friend * show_DB(friend * frnds_DB, size_t *n);//show DB

friend * delete_by_num(friend *frnds_DB, size_t *n, size_t i);//delete element by num

friend * select_sort_DB_by_field(friend *frnds_DB, size_t n, comp_func cmp);//select sort DB by field

friend * pie_diagram(friend *frnds_DB, size_t s, size_t e, size_t n);//draw pie diagram

friend * rect_diagram(friend *frnds_DB, size_t s, size_t e, size_t n);//draw rectangle diagram


#endif // DATA_BASE_H_INCLUDED

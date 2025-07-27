#ifndef DB_H_INCLUDED
#define DB_H_INCLUDED

#define N 200
#define S 50
#define PI 3.1415

typedef struct friendr {
    size_t num;

    char *name;
    double cash;
    int c_frnds;
} friendr;

typedef int (*comp_func) (void *, void *);//compare function

int cmp_c_frnds(void *a, void *b);//compare function for struct friend int: struct friend -> c_frds

int cmp_cash(void *a, void *b);//compare function for struct friend double: struct friend -> cash

int cmp_char(void *a, void *b);//compare function for struct friend char*: struct friend -> char

int cmp_num(void *a, void *b);//compare function for struct friend size_t: struct friend -> num

friendr * clone_DB(friendr *frnds_DB, size_t * n);//clone friends_DB

friendr * init_DB();//initialize Data Base

friendr * fill_DB_from_file(friendr * frnds_DB, char *path, size_t *n);//fill DB from file with path "path", view of: name | cost | amount of friends|

friendr * add_friend(friendr * frnds_DB, size_t *n, char *nname, int nc_frnds, double ncash);// add friend in friends_DB

friendr * add_friend_cmd(friendr * frnds_DB, size_t *n);// add friend in friends_DB in cmd

friendr * show_DB(friendr * frnds_DB, size_t *n);//show DB

friendr * delete_by_num(friendr *frnds_DB, size_t *n, size_t i);//delete element by num

friendr * select_sort_DB_by_field(friendr *frnds_DB, size_t n, comp_func cmp);//select sort DB by field

friendr * pie_diagram(friendr *frnds_DB, size_t s, size_t e, size_t n);//draw pie diagram

friendr * rect_diagram(friendr *frnds_DB, size_t s, size_t e, size_t n);//draw rectangle diagram


#endif // DB_H_INCLUDED

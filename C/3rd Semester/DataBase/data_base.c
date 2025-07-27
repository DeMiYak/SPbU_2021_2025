#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <graphics.h>
#include <conio.h>

#include "data_base.h"
#include "sort.h"

//compare function for int: struct friend -> c_frds
int cmp_c_frnds(void *a, void *b){

    return ((friend *)a)->c_frnds < ((friend *)b)->c_frnds;
}

//compare function for struct friend double: struct friend -> cash
int cmp_cash(void *a, void *b){

    return ((friend *)a)->cash < ((friend *)b)->cash;
}

//compare function for struct friend char*: struct friend -> char
int cmp_char(void *a, void *b){

    return strlen(((friend *)a)->name) < strlen(((friend *)b)->name);
}

//compare function for struct friend num: struct friend -> num
int cmp_num(void *a, void *b){

    return ((friend *)a)->num < ((friend *)b)->num;
}

//initialize Data Base
friend * init_DB(){

    friend *frnds_DB = malloc(N * sizeof(friend));

    if(!frnds_DB) return NULL;

    return frnds_DB;
}

//clone friends_DB
friend * clone_DB(friend *frnds_DB, size_t * n){

    if(!frnds_DB) return NULL;

    friend *c_frnds_DB = malloc(N * sizeof(friend));

    if(!c_frnds_DB) return NULL;

    memcpy(c_frnds_DB, frnds_DB,N * sizeof(friend));

    if(!c_frnds_DB) return NULL;

    return c_frnds_DB;

}

// add friend in friends_DB
friend * add_friend(friend * frnds_DB, size_t *n, char *nname, int nc_frnds, double ncash){

    if(!frnds_DB ||  frnds_DB[*n].cash < 0 ||  frnds_DB[*n].c_frnds < 0) return NULL;

    frnds_DB[*n].name = malloc(S*sizeof(char));

    if(!nname || !frnds_DB[*n].name) return NULL;

    memcpy(frnds_DB[*n].name, nname, S*sizeof(char));

    frnds_DB[*n].cash = ncash;
    frnds_DB[*n].c_frnds = nc_frnds;
    frnds_DB[*n].num = *n + 1;

    ++*n;

    return frnds_DB;
}

// add friend in friends_DB in cmd
friend * add_friend_cmd(friend * frnds_DB, size_t *n){

    if(!frnds_DB) return NULL;

    char nname[S];
    int nc_frnds;
    double ncash;

    printf("Input name: ");
    fflush(stdin);
    fgets(nname, S, stdin);
    printf("Input amount of frieds: ");
    scanf("%d", &nc_frnds);
    printf("Input cash: ");
    scanf("%lf", &ncash);

    nname[strlen(nname)  -1] = '\0';

    add_friend(frnds_DB, n, nname, nc_frnds, ncash);

    return frnds_DB;
}

//fill DB from file with path "path", view of: name | cost | amount of friends|
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

//delete element by num
friend * delete_by_num(friend *frnds_DB, size_t *n, size_t i){

    if(!frnds_DB) return NULL;

    if(i > *n)return NULL;

    size_t j = 0;

    while(frnds_DB[j].num != i){++j;}

    if(j != *n){
        frnds_DB[j].cash = frnds_DB[*n-1].cash;
        frnds_DB[j].c_frnds = frnds_DB[*n-1].c_frnds;
        memcpy(frnds_DB[j].name, frnds_DB[*n-1].name, S*sizeof(char));
    }

    --*n;

    return frnds_DB;
}

//select sort DB by field
friend * select_sort_DB_by_field(friend *frnds_DB, size_t n, comp_func cmp){

    if(!frnds_DB) return NULL;

    sort_select(frnds_DB, n, sizeof(friend), cmp);

    for(size_t i = 0; i < n; ++i){
        frnds_DB[i].num = i+1;
    }

    return frnds_DB;
}

//show DB
friend * show_DB(friend * frnds_DB, size_t *n){

    if(!frnds_DB) return NULL;
    printf("num\t|name\t\t|amout of friends|cash\t\t|\n");
    printf("----------------------------------------------------------\n");

    for(size_t i = 0; i < *n; ++i){
        printf("%-8Iu|%-15s|%-16d|%-15.2lf|\n", frnds_DB[i].num, frnds_DB[i].name, frnds_DB[i].c_frnds, frnds_DB[i].cash);
    }

    return frnds_DB;
}

//draw pie diagram
friend * pie_diagram(friend *frnds_DB, size_t s, size_t e, size_t n){

    if(!frnds_DB || s >= n || e - s >= n || s >= e || s < 1) return NULL;

    int gd = CUSTOM;
    int gm = CUSTOM_MODE(1000, 600);
    double sum;
    double prev = 0, next = 0;
    size_t k;

    printf("You want pie diagram on: \n 1)Cash data\n 2)Amount of friends data\n");
    scanf("%Iu", &k);

    initgraph(&gd, &gm, "");//open graphic mode


    switch(k){
        case 1:

            for(size_t i = s - 1; i < e; ++i){
                sum += frnds_DB[i].cash;
            }

            next = 360/sum*frnds_DB[s - 1].cash;

            if((int)frnds_DB[s - 1].cash != 0){
                    setfillstyle(1, (s)%15);
                    setcolor((s)%15);
                    pieslice(300, 300, (int)prev, (int)next, 200);
                    bar(525, 100, 535, 110);
                    setcolor(15);
                    outtextxy(250, 50, "Pie diagram of friends cash");
                    outtextxy(540, 100, frnds_DB[s - 1].name);
            }else{
                setfillstyle(1, (s)%15);
                setcolor((s)%15);
                bar(525, 100, 535, 110);
                setcolor(15);
                outtextxy(250, 50, "Pie diagram of friends cash");
                outtextxy(540, 100, strcat(frnds_DB[s - 1].name, " cash = 0 ("));
            }

            for(size_t i = s; i < e; ++i){
                if((int)frnds_DB[i].cash != 0){
                    prev = next;
                    next += 360/sum*frnds_DB[i].cash;
                    setcolor((i + 1)%15);
                    setfillstyle(1, (i + 1)%15);
                    pieslice(300, 300, (int)prev, (int)next, 200);
                    bar(525, 100 + (i-s + 1)*30, 535, 110+ (i-s + 1)*30);
                    setcolor(15);
                    outtextxy(540, 100 + (i-s + 1)*30, frnds_DB[i].name);
                }else{
                    setfillstyle(1, (i + 1)%15);
                    setcolor((i + 1)%15);
                    bar(525, 100 + (i-s  + 1)*30, 535, 110 + (i-s + 1)*30);
                    setcolor(15);
                    outtextxy(540, 100 + (i-s + 1)*30, strcat(frnds_DB[i].name, " cash = 0 ("));
                }
            }


        break;
        case 2:

            for(size_t i = s - 1; i < e; ++i){
                sum += frnds_DB[i].c_frnds;
            }

            next = 360/sum*frnds_DB[s - 1].c_frnds;

            if((int)frnds_DB[s - 1].c_frnds != 0){
                    setfillstyle(1, (s)%15);
                    setcolor((s)%15);
                    pieslice(300, 300, (int)prev, (int)next, 200);
                    bar(525, 100, 535, 110);
                    setcolor(15);
                    outtextxy(250, 50, "Pie diagram of amount of friends");
                    outtextxy(540, 100, frnds_DB[s - 1].name);
            }else{
                setfillstyle(1, (s)%15);
                setcolor((s)%15);
                bar(525, 100, 535, 110);
                setcolor(15);
                outtextxy(250, 50, "Pie diagram of friends cash");
                outtextxy(540, 100, strcat(frnds_DB[s - 1].name, " cash = 0 ("));
            }

            for(size_t i = s; i < e; ++i){
                if((int)frnds_DB[i].c_frnds != 0){
                    prev = next;
                    next += 360/sum*frnds_DB[i].c_frnds;
                    setcolor((i + 1)%15);
                    setfillstyle(1, (i + 1)%15);
                    pieslice(300, 300, (int)prev, (int)next, 200);
                    bar(525, 100 + (i-s + 1)*30, 535, 110+ (i-s + 1)*30);
                    setcolor(15);
                    outtextxy(540, 100 + (i-s + 1)*30, frnds_DB[i].name);
                }else{
                    setfillstyle(1, (i + 1)%15);
                    setcolor((i + 1)%15);
                    bar(525, 100 + (i-s  + 1)*30, 535, 110 + (i-s + 1)*30);
                    setcolor(15);
                    outtextxy(540, 100 + (i-s + 1)*30, strcat(frnds_DB[i].name, " amount of friends = 0 ("));
                }
            }

        break;
        default: printf("No such command!"); return NULL;
    };

    readkey();
    closegraph();

    return frnds_DB;
}

//draw rectangle diagram
friend * rect_diagram(friend *frnds_DB, size_t s, size_t e, size_t n){
    if(!frnds_DB || s >= n || e - s >= n || s >= e || s < 1) return NULL;

    int gd = CUSTOM;
    int gm = CUSTOM_MODE(700, 600);

    size_t k, y = 0;
    double w = 100, h = 0;
    double max = 0;
    printf("You want rectangle digram on: \n 1)Cash data\n 2)Amount of friends data\n");
    scanf("%Iu", &k);

    initgraph(&gd, &gm, "");//open graphic mode

    switch(k){

    case 1:

         for(size_t i = s - 1; i < e; ++i){
                if(frnds_DB[i].cash > max){
                    max = frnds_DB[i].cash;
                }

                if((int)frnds_DB[i].cash != 0)++y;

            }

        if(max == 0){
            printf("All cash is 0. They are students");
            return NULL;
        }

        for(size_t i = s - 1; i < e; ++i){

            if((int)frnds_DB[i].cash != 0){
                    h = frnds_DB[i].cash/max * 300;
                    setfillstyle(1, (i+1)%15);
                    setcolor((i)%15);
                    bar((int)w, 500 - (int)h, (int)(w+500/y), 550);
                    setcolor(15);
                    outtextxy(250, 50, "Rectangle diagram of friend's cash");
                    outtextxy(w, 555, frnds_DB[i].name);
                    w += 500/y;
            }
        }

    break;

    case 2:

        for(size_t i = s - 1; i < e; ++i){
                if(frnds_DB[i].c_frnds > max){
                    max = frnds_DB[i].c_frnds;
                }

                if((int)frnds_DB[i].c_frnds != 0)++y;

            }

        if(max == 0){
            printf("All amount of friends is 0. They are naggers");
            return NULL;
        }

        for(size_t i = s - 1; i < e; ++i){

            if((int)frnds_DB[i].c_frnds != 0){
                    h = frnds_DB[i].c_frnds/max * 300;
                    setfillstyle(1, (i+1)%15);
                    setcolor((i)%15);
                    bar((int)w, 600 - (int)h, (int)w+500/y, 550);
                    setcolor(15);
                    outtextxy(250, 50, "Rectangle diagram of amount of friends");
                    outtextxy(w, 555, frnds_DB[i].name);
                    w += 500/y;
            }
        }

        break;

    default: printf("No such command!"); return NULL;
    };

    readkey();
    closegraph();

    return frnds_DB;
}


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "rbt.h"
#include "graph_rbt.h"

#include<graphics.h>
#include <conio.h>


void rb_tree_graph(rb_tree *t, size_t n, rb_node *nd){

    if(!t->root)return;

    char buff[12];

    int gd = CUSTOM;

    int gm = CUSTOM_MODE(1000, 1000);

    initgraph(&gd, &gm, "");//open graphic mode

    floodfill(1,1,15);

    rb_node_graph(t->root, 500, 30, 70);

    switch(n){
    case 1:
        setcolor(0);
        settextstyle(0, 0, 10);
        outtextxy(100, 10, "Done RED-BLACK tree");
        break;
    case 2:
        setcolor(0);
        settextstyle(0, 0, 7);
        outtextxy(50, 10, "RED-BLACK tree after");
        outtextxy(50, 25, "insert key as binary search tree");
        break;
    case 3:
        setcolor(0);
        settextstyle(0, 0, 7);
        outtextxy(50, 10, "RED-BLACK tree after");
        outtextxy(50, 25, "recolor (insert balance)");
        break;
    case 4:
        setcolor(0);
        settextstyle(0, 0, 7);
        outtextxy(50, 10, "RED-BLACK tree after");
        outtextxy(50, 25, "deleting node");
        break;
    case 5:
        setcolor(0);
        settextstyle(0, 0, 7);
        outtextxy(50, 10, "RED-BLACK tree after");
        outtextxy(50, 25, "recolor (deleting balance)");
        break;
    case 6:
        itoa(nd->key, buff, 10);

        setcolor(0);
        settextstyle(0, 0, 7);
        outtextxy(50, 10, "RED-BLACK tree before");
        outtextxy(50, 25, "rotate around key = ");
        outtextxy(250, 25, buff);
        break;
    case 7:
        itoa(nd->key, buff, 10);

        setcolor(0);
        settextstyle(0, 0, 7);
        outtextxy(50, 10, "RED-BLACK tree after");
        outtextxy(50, 25, "rotate around key = ");
        outtextxy(250, 25,  buff);
        break;
    case 8:
        itoa(nd->key, buff, 10);

        setcolor(0);
        settextstyle(0, 0, 7);
        outtextxy(50, 10, "RED-BLACK tree before");
        outtextxy(50, 25, "rotate around key = ");
        outtextxy(250, 25,  buff);
        break;
    case 9:
        itoa(nd->key, buff, 10);

        setcolor(0);
        settextstyle(0, 0, 7);
        outtextxy(50, 10, "RED-BLACK tree after");
        outtextxy(50, 25, "rotate around key = ");
        outtextxy(250, 25, buff);
        break;
    };

    readkey();

    closegraph();

    return;
}

void rb_node_graph(rb_node *nd, int x, int y, double fi){

    char buff[12];
    double nxl, nyl, nxr, nyr;

    itoa(nd->key, buff, 10);

    circle(x, y, 10);

    if(nd->color){
        setfillstyle(1, 0);
    }else{
        setfillstyle(1, 4);
    }


    fillellipse(x, y, 15, 15);


    setcolor(15);
    outtextxy(x - 5, y - 5, buff);

    if(nd->left){
        nxl =  x - tan(fi*3.1415926/180)*40;
        nyl = y + 40;
        setcolor(0);
        line(x - (int)(cos(fi*3.1415926/180)*20), y + (int)(sin(fi*3.1415926/180)*8), (int)nxl, (int)nyl);
        rb_node_graph(nd->left, (int)nxl, (int)nyl, fi - 5);
    }

    if(nd->right){
        nxr =  x + tan(fi*3.1415926/180)*40;
        nyr = y + 40;
        setcolor(0);
        line( x + (int)(cos(fi*3.1415926/180)*20), y + (int)(sin(fi*3.1415926/180)*8), (int)nxr, (int)nyr);
        rb_node_graph(nd->right, (int)nxr, (int)nyr, fi - 5);
    }

    return;
}

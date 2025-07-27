#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "rbt.h"
#include "graph.h"

#include<graphics.h>
#include<conio.h>


void rbt_node_graph(rb_node *n, int x, int y, double fi){

    char buff[12];
    double xL, yL, xR, yR;

    itoa(n->key, buff, 10);

    circle(x, y, 20);

    if(n->color){
        setfillstyle(1, 0);
    }else{
        setfillstyle(1, 4);
    }

    fillellipse(x, y, 20, 20);


    setcolor(15);
    outtextxy(x - 7, y - 7, buff);

    if(n->left){
        xL =  x - tan(fi*3.1415926535/180)*60;
        yL = y + 60;
        setcolor(15);
        line(x - (int)(cos(fi*3.1415926535/180)*20), y + (int)(sin(fi*3.1415926535/180)*20), (int)xL, (int)yL);
        rbt_node_graph(n->left, (int)xL, (int)yL, fi - 15);
    }

    if(n->right){
        xR =  x + tan(fi*3.1415926535/180)*60;
        yR = y + 60;
        setcolor(15);
        line(x + (int)(cos(fi*3.1415926535/180)*20), y + (int)(sin(fi*3.1415926535/180)*20), (int)xR, (int)yR);
        rbt_node_graph(n->right, (int)xR, (int)yR, fi - 12);
    }

    return;
}

void rbt_tree_graph(rb_tree *t, size_t n, rb_node *nd){

    if(!t->root)return;

    char buff[12];

    int gd = CUSTOM;

    int gm = CUSTOM_MODE(1000, 1000);

    initgraph(&gd, &gm, "");//open graphic mode

    rbt_node_graph(t->root, 500, 30, 70);

    switch(n){
    case 1:         // Print
        setcolor(15);
        settextstyle(0, 0, 10);
        outtextxy(50, 10, "RBTree");
        break;
    case 2:         // Insertion visualization
        setcolor(15);
        settextstyle(0, 0, 10);
        outtextxy(50, 10, "RBTree");
        outtextxy(50, 25, "Insertion");
        break;
    case 3:         // Recolor insertion
        setcolor(15);
        settextstyle(0, 0, 10);
        outtextxy(50, 10, "RBTree");
        outtextxy(50, 25, "Recoloring (Insertion)");
        break;
    case 4:         // Deletion visualization
        setcolor(15);
        settextstyle(0, 0, 10);
        outtextxy(50, 10, "RBTree");
        outtextxy(50, 25, "Deletion");
        break;
    case 5:         // Recolor deletion
        setcolor(15);
        settextstyle(0, 0, 10);
        outtextxy(50, 10, "RBTree");
        outtextxy(50, 25, "Recoloring (Deletion)");
        break;
    case 6:         // Pre-right-rotation
        itoa(nd->key, buff, 10);

        setcolor(15);
        settextstyle(0, 0, 10);
        outtextxy(50, 10, "RBTree preview");
        outtextxy(50, 25, "Right rotation; key = ");
        outtextxy(50, 50, buff);
        break;
    case 7:         // Right rotation
        itoa(nd->key, buff, 10);

        setcolor(15);
        settextstyle(0, 0, 10);
        outtextxy(50, 10, "RBTree");
        outtextxy(50, 25, "Right rotation; key = ");
        outtextxy(50, 50,  buff);
        break;
    case 8:         // Pre-left-rotation
        itoa(nd->key, buff, 10);

        setcolor(15);
        settextstyle(0, 0, 10);
        outtextxy(50, 10, "RBTree preview");
        outtextxy(50, 25, "Left rotation; key = ");
        outtextxy(50, 50,  buff);
        break;
    case 9:         // Left rotation
        itoa(nd->key, buff, 10);

        setcolor(15);
        settextstyle(0, 0, 10);
        outtextxy(50, 10, "RBTree");
        outtextxy(50, 25, "Left rotation; key = ");
        outtextxy(50, 50, buff);
        break;
    };

    readkey();

    closegraph();

    return;
}



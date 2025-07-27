#ifndef MATRIXSTRUCT_H_INCLUDED
#define MATRIXSTRUCT_H_INCLUDED
#include<stddef.h>

#define SIZE_CONST 1000
/**
//Stat
typedef struct matrixStat
{
    size_t hor, vert; // l -> (1 2 3 4 5 6), w -> (1 2 3 4 5 6)T
    double mat[SIZE_CONST][SIZE_CONST];
} matrixStat;

matrixStat *matrixStat_alloc(size_t i, size_t j);

matrixStat *matrixStat_clone(const matrixStat *m);

void matrixStat_free(matrixStat *m);

double *matrixStat_get(matrixStat *m, size_t i, size_t j);
*/
//Dyn
/*
typedef struct matrixDyn
{
    size_t hor, vert;
    double **mat;
}matrixDyn;

matrixDyn *matrixDyn_alloc(size_t i, size_t j);

matrixDyn *matrixDyn_clone(const matrixDyn *m);

void matrixDyn_free(matrixDyn *m);

double *matrixDyn_get(matrixDyn *m, size_t i, size_t j);

const double *matrixDyn_cget(const matrixDyn *m, size_t i, size_t j);

matrixDyn *matrixDyn_resize(matrixDyn *m, size_t i, size_t j);
*/
//Line
typedef struct matrixLine
{
    size_t hor, vert;
    double *mat;
}matrixLine;

matrixLine *matrixLine_alloc(size_t i, size_t j);

matrixLine *matrixLine_clone(const matrixLine *m);

void matrixLine_free(matrixLine *m);

double *matrixLine_get(matrixLine *m, size_t i, size_t j);

const double *matrixLine_cget(matrixLine *m, size_t i, size_t j);

matrixLine *matrixLine_resize(matrixLine *m, size_t i, size_t j);

#endif // MATRIXSTRUCT_H_INCLUDED

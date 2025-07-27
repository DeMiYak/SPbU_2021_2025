#ifndef TASK091023_H
#define TASK091023_H

#include<iostream>
#include<random>
using namespace std;

const int NROW = 8;
const int NCOL = 6;

void caterMemoryToArray(int** &array, int a_row, int a_col);
void randomFillArray(int** array, int a_row, int a_col, int seed = 1331);
void printArray(int** array, int a_row, int a_col);
void freeMemoryArray(int** array, int a_row);

#endif TASK091023_H
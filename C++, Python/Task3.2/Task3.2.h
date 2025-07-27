#ifndef TASK3_2_H
#define TASK3_2_H

const int NCOL = 10;
const int NROW = 12;
const int BUFFER_SIZE = 4096;

#include <iostream>
#include <random>
#include <fstream>

using namespace std;

void Swap(int*& a, int*& b);
// Bubble Sort
void sortArrayByLastCol(int** array, int a_row, int a_col);

void deleteRowsByLastColNeg(int** array, int& a_row, int a_col);

// Supplementary work

void caterMemoryToArray(int**& array, const int a_row, const int a_col);

void ReadArrayFromFile(int** &array, int& a_row, int& a_col, const char* FileName);

void MakeRandomArray(int& a_row, int& a_col, int** &array, mt19937& gen);

void printArray(int** array, const int a_row, const int a_col);

void freeMemoryArray(int** array, const int a_row);
#endif TASK3_2_H

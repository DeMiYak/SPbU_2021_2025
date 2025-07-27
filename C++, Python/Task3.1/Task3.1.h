#ifndef TASK3_1_H
#define TASK3_1_H

#define _CRT_SECURE_NO_WARNINGS

const int NCOL{ 10 };
const int NROW{ 12 };

const int BUFFER_SIZE{ 4096 };

#include <iostream>
#include <random>
#include <string>
#include <fstream>

using namespace std;

void Swap(int& a, int& b);

void sortArrayByLastColStatic(int array[][NCOL], int a_row, int a_col);

void deleteRowsByLastColNegStatic(int array[][NCOL], int& a_row, int a_col);

void printArrayStatic(int array[][NCOL], int a_row, int a_col);

void ReadArrayFromFile(int array[][NCOL], int& a_row, int& a_col, const char* FileName);

void MakeRandomArray(int &a_row, int &a_col, int array [][NCOL], mt19937 &gen);

#endif TASK3_1_H
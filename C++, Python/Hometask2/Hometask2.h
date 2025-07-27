#ifndef HOMETASK2_H
#define HOMETASK2_H

#include<iostream>
#include<stdio.h>

const size_t BUFFER_SIZE = 4096;

using namespace std;

constexpr size_t CAPDEFAULT = 1;

void initCharArray(char** &array, const size_t& capacity);
void increaseCapacity(size_t& capacity);
void resizeCharArrayAtCap(char** &array, const size_t& size, size_t& capacity);
void fillCharArray(char** &array, size_t& size, size_t& capacity);
void printCharArray(char** array, const size_t& size);
void deleteCharArray(char** array, const size_t& size);

// test1: *f a b c d e f g h i j k l *
// test2: *
// test3: '\n' '\n' *
// test4: ** fd *

#endif


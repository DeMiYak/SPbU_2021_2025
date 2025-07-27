#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
const int NMARK = 5;
const int NSYMB = 10;
const int NSTUDENT = 100;

const int NULLMARK = 0;
const int MAXMARK = 100;

struct STUDENT {
    char name[NSYMB];
    int mark[NMARK];
    float avr;
};

int input_all(STUDENT* l);

void comput_avr(STUDENT* l, int n);

void sort(STUDENT* l, int n, int (*compare)(const STUDENT&, const STUDENT&));

void to_file(const char* fname, STUDENT* l, int n);

void from_file(const char* fname, STUDENT* l, int& pn);

STUDENT* search(const STUDENT& ls, STUDENT* l, int n, int (*compare)(const STUDENT&, const STUDENT&));

void print_one(const STUDENT& ls);

void print_all(STUDENT* l, int n);

int cmp_name(const STUDENT& sOne, const STUDENT& sTwo);

int cmp_mark(const STUDENT& sOne, const STUDENT& sTwo);

int cmp_avr(const STUDENT& sOne, const STUDENT& sTwo);

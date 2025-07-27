#include<iostream>
#include<random>
#include"ArrayGen.h"

const int min = INT_MIN;
const int max = INT_MAX;

int main() {
	std::random_device rd;
	std::mt19937 engine(rd());
	std::uniform_int_distribution<> int_distr(min, max);
	return 0;
}
#pragma once

#include <iostream>
#include <optional>

using namespace std;
using optd = std::optional<double>;
using func = double(*) (double);

double f(double x);

inline bool checkRoot(double stVal, double endVal);

optd findRoot(func f, double segBeg, double segEnd, double eps = 1e6);
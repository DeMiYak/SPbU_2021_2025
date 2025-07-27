#pragma once
#include<vector>

using namespace std;

double norm(const vector<vector<double>>& vec);

double norm_subtract(const vector<vector<double>>& vec_main, const vector<vector<double>>& vec_sub);

vector<double> SolveTriagonalMatrix(vector<double>a, vector<double>b, vector<double>c, vector<double>d);
#pragma once

#include<iostream>	// KMP, BM, RK
#include<vector>	// KMP, BM, RK
#include<string>	// KMP, BM, RK
#include<map>		// BM
#include<algorithm>	// BM
#include<cmath>		// RK

using namespace std;

const int D = 256;
const int Q = 101;

vector<int> computeLPSArray(const string& pattern);
void KMPSearch(const string& text, const string& pattern);

map<char, int> buildBadCharTable(const string& pattern);
void BoyerMooreSearch(const string& text, const string& pattern);

void RabinKarpSearch(const string& text, const string& pattern);
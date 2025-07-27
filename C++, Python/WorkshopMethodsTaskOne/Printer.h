#pragma once
#include"BaseMethodGenerator.h"
#include"Resolver.h"

class PRINTER {
public:
	PRINTER(RESOLVER _resolver,
		BaseMethodGenerator* _bmg,
		vector<vector<double>> _Ustar) :
		resolver(_resolver),
		bmg(_bmg), 
		Ustar(_Ustar) {};
	void PrintTable();
private:
	void PrintUstar();
	double Discrepancy(const vector<vector<double>>& vec, const RESOLVER& resolver);
	RESOLVER resolver;
	BaseMethodGenerator* bmg;
	vector<vector<double>> Ustar;
};

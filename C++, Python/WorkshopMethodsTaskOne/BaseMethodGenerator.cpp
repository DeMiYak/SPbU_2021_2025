#include "BaseMethodGenerator.h"

void BaseMethodGenerator::Re_Calculate(sizetype _iter_num, const RESOLVER& resolver)
{
	if (iter_num == _iter_num) return;
	else if (iter_num < _iter_num) {
		for (sizetype i = iter_num; i < _iter_num; ++i) {
			IterateOnce(resolver);
		}
		iter_num = _iter_num;
	}
	else {
		iter_num = _iter_num;
		Calculate(resolver);
	}
}

void BaseMethodGenerator::PrintData()
{
	sizetype Nx = resU.size(), My = resU[0].size();
	cout << endl << "Number of iterations: " << iter_num << endl;
	for (int i = My - 1; i >= 0; --i) {
		for (int j = 0; j < Nx; ++j) {
			cout << resU[j][i] << setw(7);
		}
		cout << endl;
	}
	cout << endl;
}

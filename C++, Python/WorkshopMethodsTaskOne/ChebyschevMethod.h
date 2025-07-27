#pragma once
#include"BaseMethodGenerator.h"
//1.5.Итерационный метод с чебышевским набором параметров.

class ChebyschevMethod : public BaseMethodGenerator {
public:
	ChebyschevMethod(sizetype _iter_num) :
		BaseMethodGenerator(_iter_num), sp_par(0) {};

	ChebyschevMethod(sizetype _iter_num, const RESOLVER& resolver) :
		BaseMethodGenerator(_iter_num), sp_par(0) {
		Calculate(resolver);
	}
	//virtual void Re_Calculate(sizetype iter_num, const RESOLVER& resolver) override;
	virtual void Calculate(const RESOLVER& resolver) override;
	virtual void ChangeIterNum(sizetype _iter_num) override;
	//virtual void PrintData() override;
	virtual void PrintName() override;
private:
	double sp_par;
	virtual void IterateOnce(const RESOLVER& resolver) override;
	/*vector<double> FindChebyshevSequence(int two_degree);*/
};

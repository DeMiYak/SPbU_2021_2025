#pragma once
#include"BaseMethodGenerator.h"
//1.7.Попеременно - треугольный итерационный метод с чебышевским набором параметров.

class ChebyschevTriangleMethod : public BaseMethodGenerator {
public:

	ChebyschevTriangleMethod(sizetype _iter_num) :
		BaseMethodGenerator(_iter_num), 
		omega(1.5), 
		tau(0.8),
		gamma_1(1),
		gamma_2(1) {};

	ChebyschevTriangleMethod(sizetype _iter_num, const RESOLVER& resolver) :
		ChebyschevTriangleMethod(_iter_num) {
		Calculate(resolver);
	}
	//virtual void Re_Calculate(sizetype iter_num, const RESOLVER& resolver) override;
	virtual void Calculate(const RESOLVER& resolver) override;
	virtual void ChangeIterNum(sizetype _iter_num) override;
	//virtual void PrintData() override;
	virtual void PrintName() override;
	// Лишние методы?
	void ChangeOmega(double _omega);
	void ChangeTau(double _tau);
private:
	double omega, tau;
	double gamma_1, gamma_2;
	virtual void IterateOnce(const RESOLVER& resolver) override;
};

#pragma once
#include"BaseMethodGenerator.h"
//1.6.Попеременно треугольный итерационный метод.

class TriangleMethod : public BaseMethodGenerator {
public:

	TriangleMethod(sizetype _iter_num) :
		BaseMethodGenerator(_iter_num), omega(1.5), tau(0.8) {};

	TriangleMethod(sizetype _iter_num, const RESOLVER& resolver) :
		BaseMethodGenerator(_iter_num), omega(1.5), tau(0.8) {
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
	virtual void IterateOnce(const RESOLVER& resolver) override;
};


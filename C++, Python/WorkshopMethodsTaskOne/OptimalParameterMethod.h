#pragma once
#include"BaseMethodGenerator.h"
//1.2 Метод итерации с оптимальным параметром.

/// <summary>
/// Метод итерации с оптимальным параметром. Желательно, чтобы
/// он был внутри метода как поле класса, чтобы характеризовать
/// метод. 
/// </summary>
class OptimalParameterMethod : public BaseMethodGenerator {
public:
	OptimalParameterMethod(sizetype _iter_num) :
		BaseMethodGenerator(_iter_num) {
		opt_par = 0;
	};

	OptimalParameterMethod(sizetype _iter_num, const RESOLVER& resolver) :
		BaseMethodGenerator(_iter_num) {
		opt_par = 0;
		Calculate(resolver);
	}
	//virtual void Re_Calculate(sizetype iter_num, const RESOLVER& resolver) override;
	virtual void Calculate(const RESOLVER& resolver) override;
	virtual void ChangeIterNum(sizetype _iter_num) override;
	//virtual void PrintData() override;
	virtual void PrintName() override;
private:
	double opt_par;
	virtual void IterateOnce(const RESOLVER& resolver) override;
};
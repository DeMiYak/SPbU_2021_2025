#pragma once
#include"BaseMethodGenerator.h"

// 2.2. Метод переменных направлений 
class AlternateDirectionMethod :public BaseMethodGenerator {
public:

	AlternateDirectionMethod(sizetype _iter_num) :
		BaseMethodGenerator(_iter_num), t(1) {};

	AlternateDirectionMethod(sizetype _iter_num, const RESOLVER& resolver) :
		BaseMethodGenerator(_iter_num), t(1) {
		Calculate(resolver);
	}

	virtual void Calculate(const RESOLVER& resolver) override;
	virtual void ChangeIterNum(sizetype _iter_num) override;
	virtual void PrintName() override;
private:
	double t;
	/*void ApplyTriagonalAlg();*/
	virtual void IterateOnce(const RESOLVER& resolver) override;
};
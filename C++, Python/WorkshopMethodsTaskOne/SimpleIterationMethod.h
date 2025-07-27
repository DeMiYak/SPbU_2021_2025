#pragma once
#include"BaseMethodGenerator.h"
//1.1 Метод простой итерации.
class SimpleIterationMethod : public BaseMethodGenerator {
public:

	SimpleIterationMethod(sizetype _iter_num) : 
		BaseMethodGenerator(_iter_num) {};

	SimpleIterationMethod(sizetype _iter_num, const RESOLVER& resolver) :
		BaseMethodGenerator(_iter_num) {
		Calculate(resolver);
	}
	
	virtual void Calculate(const RESOLVER& resolver) override;
	virtual void ChangeIterNum(sizetype _iter_num) override;
	//virtual void Re_Calculate(sizetype _iter_num, const RESOLVER& resolver) override;
	//virtual void PrintData() override;
	virtual void PrintName() override;
private:
	virtual void IterateOnce(const RESOLVER& resolver) override;
};
#pragma once
#include"BaseMethodGenerator.h"
//1.3.Ìועמה Çויהוכÿ.

class SeidelMethod : public BaseMethodGenerator {
public:
	SeidelMethod(sizetype _iter_num) :
		BaseMethodGenerator(_iter_num) {};

	SeidelMethod(sizetype _iter_num, const RESOLVER& resolver) :
		BaseMethodGenerator(_iter_num) {
		Calculate(resolver);
	}
	//virtual void Re_Calculate(sizetype iter_num, const RESOLVER& resolver) override;
	virtual void Calculate(const RESOLVER& resolver) override;
	virtual void ChangeIterNum(sizetype _iter_num) override;
	//virtual void PrintData() override;
	virtual void PrintName() override;
private:
	virtual void IterateOnce(const RESOLVER& resolver) override;
};
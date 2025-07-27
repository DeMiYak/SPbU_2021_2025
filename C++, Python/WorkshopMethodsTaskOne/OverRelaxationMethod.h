#pragma once
#include"BaseMethodGenerator.h"

//1.4.Метод верхней релаксации.
class OverRelaxationMethod : public BaseMethodGenerator {
public:
	OverRelaxationMethod(sizetype _iter_num) :
		BaseMethodGenerator(_iter_num), omega(1.5) {};

	OverRelaxationMethod(sizetype _iter_num, const RESOLVER& resolver, double _omega = 1.5) :
		BaseMethodGenerator(_iter_num), omega(_omega) {
		if (omega > 2 || omega < 0) { omega = 1.5; }
		Calculate(resolver);
	}
	//virtual void Re_Calculate(sizetype iter_num, const RESOLVER& resolver) override;
	virtual void Calculate(const RESOLVER& resolver) override;
	virtual void ChangeIterNum(sizetype _iter_num) override;
	//virtual void PrintData() override;
	virtual void PrintName() override;
	void ChangeOmega(double _omega);
private:
	double omega;
	virtual void IterateOnce(const RESOLVER& resolver) override;
};
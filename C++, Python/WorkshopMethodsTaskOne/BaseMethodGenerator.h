#pragma once
#include"Resolver.h"
#include<iostream>

/// <summary>
/// "—келет дл€ методов", что необходимо:
/// 1. виртуальный метод дл€ вычислений (Calculate)
/// 2. возможно, вывод полученных вычислений (PrintData)
/// 3. класс RESOLVER дл€ выполнени€ вычислений
/// 4. поле типа sizetype (size_t) дл€ обозначени€ итераций,
/// причЄм, при изменении числа итераций желательно пересчитывать
/// вычислени€ (можно сделать по хитрому, если новых итераций больше, то
/// просто проитерировать ещЄ несколько раз, а если меньше, то тут никак)
/// 5. поле типа double дл€ определени€ точности (условие остановки вместо
/// итераций) 
/// </summary>
class BaseMethodGenerator {
public:
	BaseMethodGenerator(sizetype _iter_num) { iter_num = _iter_num; }
	virtual void Calculate(const RESOLVER& resolver) = 0;
	virtual void ChangeIterNum(sizetype _iter_num) = 0;
	virtual void Re_Calculate(sizetype _iter_num, const RESOLVER& resolver);
	virtual void PrintData();
	virtual vector<vector<double>> GetResU() const { return resU; }
	virtual vector<vector<double>> GetPrevResU() const { return prevResU; }
	virtual sizetype GetIterNum() const { return iter_num; }
	virtual void PrintName() = 0;
protected:
	// ¬ведЄм resU, iter_num, чтобы содержать U_k,
	// полученный методом. “огда требуем, чтобы в резольвере
	// всегда находилс€ U_0. “о есть, резольвер - шаблон
	// дл€ вычислени€ методами
	/// <summary>
	/// «десь, вычисленный U
	/// </summary>
	vector<vector<double>> resU;
	vector<vector<double>> prevResU;
	/// <summary>
	/// „исло итераций
	/// </summary>
	sizetype iter_num;
	virtual void IterateOnce(const RESOLVER& resolver) = 0;
};
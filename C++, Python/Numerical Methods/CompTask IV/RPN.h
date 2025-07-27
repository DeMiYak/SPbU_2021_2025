#ifndef RPN_H_INCLUDED
#define RPN_H_INCLUDED

#include<vector>
#include<string>
#include<cmath>
#include<cstdlib>
#include<stack>
#include<iostream>
#include<iomanip>

using namespace std;

class Formula {
public:

    Formula(){_formula = "0";}

    Formula(string formula) { _formula = formula; }

    Formula(const Formula &formula) {
        _formula = formula._formula;
    };

    double Evaluate(double x);

    Formula operator*(const Formula &formulaTwo) {
        return *this * formulaTwo._formula;
    };

    Formula operator*(const string &formulaTwo) {
        ;
        return Formula('(' + this->_formula + ")*(" + formulaTwo + ')');
    };

    friend Formula operator*(const string &formulaOne, const Formula &formulaTwo) {
        return Formula('(' + formulaOne + ")*(" + formulaTwo._formula + ')');
    };

private:

    string _formula;

    bool delimiter(char c);

    bool isOperator(char c);

    int priority(char _operator);

    void ProcessOperator(stack<double> &_stack, char _operator);

    string ReplaceVariableWithDouble(double x);

    double CalculateFromString(const string &_string);
};

#endif // RPN_H_INCLUDED

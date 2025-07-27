#ifndef INTEGRATOR_H_INCLUDED
#define INTEGRATOR_H_INCLUDED

#include"RPN.h"

class Integrator{
public:
    Integrator(Formula formula, double startingPoint, double endingPoint, int segmentNum){
        _formula = Formula(formula);
        SetValues(startingPoint, endingPoint, segmentNum);
    }

    Integrator(Formula formula){
        _formula = formula;
    }

    void SetValues(double startingPoint, double endingPoint, int segmentNum);

    double JLeftRectangle();

    double JRightRectangle();

    double JMiddleRectangle();

    double JTrapezoid();

    double JSimpson();

    double JThreeEighths();

private:

    Formula _formula;

    double _startingPoint = 0;

    double _endingPoint = 1;

    int _segmentNum = 10;

    bool ValidateValues(double startingPoint, double endingPoint, int segmentNum);
};

#endif // INTEGRATOR_H_INCLUDED

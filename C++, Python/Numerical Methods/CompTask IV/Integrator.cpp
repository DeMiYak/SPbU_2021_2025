#include"Integrator.h"

bool Integrator::ValidateValues(double startingPoint, double endingPoint, int segmentNum) {
    bool condOne = startingPoint > endingPoint;
    bool condTwo = segmentNum <= 0;
    if (condOne || condTwo) {
        if (condOne)
            wcout << L"Ошибка: конец меньше начала" << endl;
        if (condTwo)
            wcout << L"Ошибка: неположительное число разбиений" << endl;
        cout << endl;
        return false;
    }
    return true;

}


void Integrator::SetValues(double startingPoint, double endingPoint, int segmentNum) {
    if (ValidateValues(startingPoint, endingPoint, segmentNum)) {
        _startingPoint = startingPoint;
        _endingPoint = endingPoint;
        _segmentNum = segmentNum;
    }
}


double Integrator::JLeftRectangle() {
    double integralResult = 0;
    double step = (_endingPoint - _startingPoint) / _segmentNum;

    for (int stepNum = 0; stepNum < _segmentNum; stepNum++) {
        double x = _startingPoint + step * stepNum;
        integralResult += _formula.Evaluate(x);
    }

    return step * integralResult;
}

double Integrator::JRightRectangle() {
    double integralResult = 0;
    double step = (_endingPoint - _startingPoint) / _segmentNum;

    for (int stepNum = 0; stepNum < _segmentNum; stepNum++) {
        double x = _startingPoint + step * (stepNum + 0.5);
        integralResult += _formula.Evaluate(x);
    }

    return step * integralResult;
}

double Integrator::JMiddleRectangle() {
    double integralResult = 0;
    double step = (_endingPoint - _startingPoint) / _segmentNum;

    for (int stepNum = 0; stepNum < _segmentNum; stepNum++) {
        double x = _startingPoint + step * (stepNum + 0.5);
        integralResult += _formula.Evaluate(x);
    }
    return step * integralResult;
}

double Integrator::JTrapezoid() {
    double integralResult = 0;
    double step = (_endingPoint - _startingPoint) / _segmentNum;
    double x = _startingPoint;
    for (int stepNum = 0; stepNum < _segmentNum; stepNum++) {
        double y = _startingPoint + step * (stepNum + 1);
        integralResult += (_formula.Evaluate(x) + _formula.Evaluate(y)) / 2;

        x = y;
    }

    return step * integralResult;
}

double Integrator::JSimpson() {
    double integralResult = 0;
    double step = (_endingPoint - _startingPoint) / _segmentNum;
    double x = _startingPoint;
    for (int stepNum = 0; stepNum < _segmentNum; stepNum++) {
        double y = _startingPoint + step * (stepNum + 1);
        double betweenXY = (x + y) / 2;
        integralResult += (_formula.Evaluate(x) + 4 * _formula.Evaluate(betweenXY) + _formula.Evaluate(y)) / 6;

        x = y;
    }

    return step * integralResult;
}

double Integrator::JThreeEighths() {
    double integralResult = 0;
    double step = (_endingPoint - _startingPoint) / _segmentNum;
    double x = _startingPoint;

    for (int stepNum = 0; stepNum < _segmentNum; stepNum++) {
        double xOneThird = x + step / 3;
        double y = _startingPoint + step * (stepNum + 1);
        double yOneThird = y - step / 3;
        integralResult += (_formula.Evaluate(x) + 3 * (_formula.Evaluate(xOneThird) + _formula.Evaluate(yOneThird)) + _formula.Evaluate(y)) / 8;

        x = y;
    }

    return step * integralResult;
}


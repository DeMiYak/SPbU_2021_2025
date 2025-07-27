#ifndef SUP_H_INCLUDED
#define SUP_H_INCLUDED
// Line
/**
* ������� findab ������� �������� ����� �������������;
*/
void findabLine(double xy, double xx, double xi, double yi, size_t n, double* a, double* b);


/**
* ������� ������ � ����� �������������, � ����� ���������� �� �� �������;
*/
void getFullAnswerLine(double delta, double dela, double delb, double anew, double bnew);

/**
* ��������� �������������� ������ ��������� ��������� � ������ ��������� �����
*/
void deltaCalcLine(double dela, double delb, size_t n, double *delta, double *wrvala, double *wrvalb, double *wrvaleq);

// Square

/**
* ������� �������� ����� ������������� ����������� ���������
*/
void findabSquare(double x2yC, double xxC, double xx2C, double xyC, double x2x2C, double *a, double *b);

/**
* ������� ������ � ����� ������������� ����������� ���������
*/
void getFullAnswerSquare(double delta, double dela, double delb, double delc, double anew, double bnew, double cnew);

/**
* ��������� �������������� ������ ��������� ��������� � ������ ��������� �����
*/
void deltaCalcSquare(double dela, double delb, double delc, size_t n, double *delta, double *wrvala, double *wrvalb, double *wrvalc, double *wrvaleq);

/**
* ���������� ������������ ������������� ������ ����� ��������
* (������������ ����� ����������� ������� �� �������� - ������ � ����� ���������)
*/
void findabcQ(double a, double b, size_t n, double *aQ, double *bQ, double *cQ);

int cmp(const double *a, const double *b);
#endif // SUP_H_INCLUDED

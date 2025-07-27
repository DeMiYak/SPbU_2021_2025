#ifndef SUP_H_INCLUDED
#define SUP_H_INCLUDED

/**
* ������� loadup ������� ����� xn*xn, xn, yn, xn*yn, ��� n = 0, 1, ..., i - 1
* i - ���������� �������� ����� ������������ �����
*/
void loadup(double *xy, double *xx, double *xi, double *yi, int i, double x[], double y[]);

/**
* ������� arrayx ��������� ������� x, y ����������� ������� �����
* �������� ����� (x, y) ����� ������
* (��� ������� ��������� ���, ���� �� ����)
*/
void arrayx(double x[], double y[], int i);

/**
* ������� findsolution ������� �� ����� ������������ �������� �����������
* �������� � � b ���������� �� ������ �������
*/
void findsolution(double xy, double xx, double xi, double yi, int i);

#endif // SUP_H_INCLUDED

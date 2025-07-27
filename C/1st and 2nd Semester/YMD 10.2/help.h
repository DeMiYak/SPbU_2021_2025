#ifndef Pigeon
#define Pigeon

// ������������� ��������, ������� ����� ���������� �� ����� ����������
enum QuadStatus
{
    ERROR,              /*NAN or INF*/
    TWO_ROOTS,          /*��� �����*/
    ONE_ROOT,           /*���� ������*/
    ANY_NUMBER,         /*����� ������������ �����*/
    NO_ROOTS,           /*��� ������*/
    TWO_COMPLEX_ROOTS   /*��� ����������� �����*/
};
// ��������� ����� ����������� ��������� � ��������� �� �����
enum QuadStatus QuadFunc(double a, double b, double c, double *root1, double *root2);



#endif // Pigeon

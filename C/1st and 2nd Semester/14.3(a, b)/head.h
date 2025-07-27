#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

/**
* ������� ��������� ������
* ������� ������: ������, ������� ���������, ����� �������, ������� ���������
* �����: ��������� �� ��������� �������, ���� ������� (� ��������� ������ NULL)
*/
void *BinSearch(void *, void *, size_t, size_t, int (*compare)(const void *, const void *));

/**
* ������� ��������� �����
* ������� ������: ������, ������� ���������, ����� �������, ������� ���������
* �����: ��������� �� �����, ���� ���������� ������� ��������� � ������������� �������
*/
void *BinPlace(void *, void *, size_t, size_t, int (*compare)(const void *, const void *));


void arrFill(int *, size_t);

#endif // HEAD_H_INCLUDED

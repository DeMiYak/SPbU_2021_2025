#include <stddef.h>
#include "head.h"

long LenStr(const char *s); // ����� ������

void SubS(char *s, char *newS, size_t n, size_t m); // ��������� ������ ���������

void SubStr(char *s, char *newS, long n, long m) {
    long len = LenStr(s);
    if (n < 0)n += len; // �������� � ��� ������ �
    if (m < 0) {    // ���� ����� ������������
        n += m + 1; // ������ ���������� �� -(� + 1)
        m = -m;     // ����� �������� ������������� ��������

    }
    if (n < 0) {    // ���� �������� ����� �� ��������
        m += n;     // ������� �����
        n = 0;      // ��������� � � ������
    }
    if (n >= len || m < 0) { // ���� � �������� ������ �� ������� ��� � ������������
        newS[0] = '\0';
        return;
    }
    if (n + m >= len || m == 0) {
        m = len - n;
    }
    SubS(s, newS, n, m); // ��������� ������� �������� ��������� ������ ���������
}

long LenStr(const char *s) {
    long len = 0;
    for (const char *i = s; *i != '\0'; ++i, ++len);
    return len;
}


void SubS(char *s, char *newS, size_t n, size_t m) {
    char *j = newS;
    for (char *i = s + n; *i != '\0' && m > 0; ++i, ++j, --m) {
        *j = *i;
    }
    *j = '\0';
}


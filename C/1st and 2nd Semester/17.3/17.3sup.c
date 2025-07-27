#include <stddef.h>
#include "head.h"

long LenStr(const char *s); // длина строки

void SubS(char *s, char *newS, size_t n, size_t m); // выделение нужной подстроки

void SubStr(char *s, char *newS, long n, long m) {
    long len = LenStr(s);
    if (n < 0)n += len; // фиксация н для любого н
    if (m < 0) {    // если длина отрицательна
        n += m + 1; // начало сдвигается на -(м + 1)
        m = -m;     // длина получает положительное значение

    }
    if (n < 0) {    // если осталось слева за массивом
        m += n;     // срезаем длину
        n = 0;      // фиксируем н в начале
    }
    if (n >= len || m < 0) { // если н оказался справа от массива или м отрицательна
        newS[0] = '\0';
        return;
    }
    if (n + m >= len || m == 0) {
        m = len - n;
    }
    SubS(s, newS, n, m); // выполняем функцию создания выделения нужной подстроки
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


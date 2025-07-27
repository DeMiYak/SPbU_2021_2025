#include <stdio.h>

void BuildStarStr(char s[], int n) {
    for (int i = 0; i < n; ++i) {
        s[i] = '*';
    }
    s[n] = '\0';
}

void BuildStarAndSpaceStr(char s[], int n, int d) {
    for (int i = 0; i < d; ++i) {
        s[i] = '*';
    }
    for (int i = d; i < n - d; ++i) {
        s[i] = ' ';
    }
    for (int i = n - d; i < n; ++i) {
        s[i] = '*';
    }
    s[n] = '\0';
}

void StarPrint(int n, int m, int d) {
    if (d * 2 < m && d * 2 < n) {
        char ws[n + 1], hs[n + 1];
        BuildStarStr(ws, n);
        for (int i = 0; i < d; ++i) {
            printf("%s\n", ws);
        }
        BuildStarAndSpaceStr(hs, n, d);
        for (int i = 0; i < m - d * 2; ++i) {
            printf("%s\n", hs);
        }
        for (int i = 0; i < d; ++i) {
            printf("%s\n", ws);
        }
    } else {
        char s[n + 1];
        BuildStarStr(s, n);
        for (int i = 0; i < n; ++i) {
            printf("%s\n", s);
        }
    }
}

int main() {
    int n, m, d;
    scanf("%i%i%i", &n, &m, &d);
    StarPrint(n, m, d);
    return 0;
}

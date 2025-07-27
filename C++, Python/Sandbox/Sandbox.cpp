// Sandbox.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "KMP.h"

int main()
{
    string text1 = "ABABDABACDABABCABAB";
    string pattern1 = "ABABCABAB";
    cout << "Text: " << text1 << "\nPattern: " << pattern1 << endl;
    KMPSearch(text1, pattern1);
    BoyerMooreSearch(text1, pattern1);
    RabinKarpSearch(text1, pattern1);
}


#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "static_array_transformation.h"

using namespace std;

int main()
{
    arr_type mat[N_MAX][N_MAX];

    //Проверка тестов
    cout << "Tests for static array:" << endl;
    int n_row, n_col;
    std::string str1 = "tests/test";
    std::string str2 = ".txt";
    std::string str;

    //Тесты на смену мин макс
    cout << "Min max tests: " << endl;
    for (int i = 1; i <= 6; ++i) {
        str.append(str1);
        str.append(std::to_string(i));
        str.append(str2);
        read_arr_from_file(mat, n_row, n_col, str.c_str());
        cout << "Test " << i << ":" << endl;
        print_arr(mat, n_row, n_col);
        cout << endl;

        //Преобразования
        change_min_and_max_rows(mat, n_row, n_col);
        cout << "Array after transformation:" << endl;
        print_arr(mat, n_row, n_col);

        cout << "------------------" << endl;
        str = "";
    }
    cout << endl << "||||||||||||||||||||||||||||||||||||||||||||||||" << endl << endl;
    //Тесты в целом 
    cout << "Delete like first row tests: " << endl;
    for (int i = 1; i <= 6; ++i) {
        str.append(str1);
        str.append(std::to_string(i));
        str.append(str2);
        read_arr_from_file(mat, n_row, n_col, str.c_str());
        cout << "Test " << i << ":" << endl;
        print_arr(mat, n_row, n_col);
        cout << endl;

        //Преобразования
        delete_rows_like_first(mat, n_row, n_col);
        cout << "Array after transformation:" << endl;
        print_arr(mat, n_row, n_col);

        cout << "------------------" << endl;
        str = "";
    }

    cout << endl << "||||||||||||||||||||||||||||||||||||||||||||||||" << endl << endl;

    //Тесты в целом 
    cout << "Full tests: " << endl;
    for (int i = 1; i <= 6; ++i) {
        str.append(str1);
        str.append(std::to_string(i));
        str.append(str2);
        read_arr_from_file(mat, n_row, n_col, str.c_str());
        cout << "Test " << i << ":" << endl;
        print_arr(mat, n_row, n_col);
        cout << endl;

        //Преобразования
        change_min_and_max_rows(mat, n_row, n_col);
        delete_rows_like_first(mat, n_row, n_col);
        cout << "Array after transformation:" << endl;
        print_arr(mat, n_row, n_col);

        cout << "------------------" << endl;
        str = "";
    }

}

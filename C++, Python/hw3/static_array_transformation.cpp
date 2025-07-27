//
// Created by SICH on 12.10.2023.
//
#define _CRT_SECURE_NO_WARNINGS
#include "static_array_transformation.h"
#include <iostream>

using namespace std;

bool check_boundaries(long n_row, long n_col) {
    return n_row > 0 && n_col > 0;
}

void change_min_and_max_rows(arr_type arr[N_MAX][N_MAX], int n_row, int n_col) {
    //����������� � ������������ ������ �������� ���������� ��� ������ ������
    arr_type max_sum = 0;
    for (int j = 0; j < n_col; max_sum += arr[0][j], ++j);
    int max_sum_i = 0;
    arr_type min_sum = max_sum;
    int min_sum_i = 0;
    for (int i = 1; i < n_row; ++i) {
        arr_type sum = 0;
        for (int j = 0; j < n_col; ++j) {
            sum += arr[i][j];
        }
        //�������� �� ����
        if (sum > max_sum) {
            max_sum = sum;
            max_sum_i = i;
        }
        //�������� �� ���
        if (sum < min_sum) {
            min_sum = sum;
            min_sum_i = i;
        }
    }

    //��������� ��� � ����
    //���� ��� ������ ���������, ������ �� ������
    if (min_sum_i == max_sum_i)
        return;
    arr_type temp;
    for (int j = 0; j < n_col; j++) {
        temp = arr[min_sum_i][j];
        arr[min_sum_i][j] = arr[max_sum_i][j];
        arr[max_sum_i][j] = temp;
    }
}

void print_arr(arr_type arr[N_MAX][N_MAX], int n_row, int n_col) {
    //���� ������ ����
    if (n_row == 0 || n_col == 0) {
        cout << "Empty array" << endl;
        return;
    }
    for (int i = 0; i < n_row; i++) {
        for (int j = 0; j < n_col; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

void delete_rows_like_first(arr_type arr[N_MAX][N_MAX], int& n_row, int n_col) {
    
    if (n_row == 0 || n_col == 0)
        return;
    // �������� ������ ������, ����� � ��� ����������
    arr_type first_row[N_MAX];
    copy(arr[0], arr[0] + n_col, first_row);

    //����� ������ ��� ������� ������ ������ ��� �����������
    int new_n = 0;
    for (int i = 0; i < n_row; ++i) {
        if (!equal(arr[i], arr[i] + n_col, first_row)) {
            copy(arr[i], arr[i] + n_col, arr[new_n]);
            ++new_n;
        }
    }
    n_row = new_n;
}


void read_arr_from_file(arr_type arr[N_MAX][N_MAX], int& n_row, int& n_col, const char*
    file_name) {

    // ������ ������� �������.
    FILE* fp = fopen(file_name, "r");
    if (fp == nullptr) {
        cout << "not open" << endl;
        return;
    }

    char buff[100];
    fscanf(fp, "%s", buff);
    n_row = strtol(buff, nullptr, 10);
    fscanf(fp, "%s", buff);
    n_col = strtol(buff, nullptr, 10);
    if (n_row > N_MAX || n_col > N_MAX) {
        cout << "Dimensionality of array more than expected. " << endl;
        n_row = 0;
        n_col = 0;
        return;
    }
    // ������ ������ �������.
    for (int i = 0; i < n_row; i++) {
        for (int j = 0; j < n_col; j++) {
            fscanf(fp, "%s", buff);
            arr[i][j] = strtol(buff, nullptr, 10);
        }
    }

    fclose(fp);
}


#include "2d_dynamic_arr.h"
#include <iostream>


void delete_arr(arr_type** arr, int n_row) {
    for (int i = 0; i < n_row; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
}


// используем &, чтобы можно было обратиться к arr и аллоцировать его
void create_arr(arr_type**& arr, int n_row, int n_col) {
    arr = new arr_type * [n_row];
    for (int i = 0; i < n_row; ++i) {
        arr[i] = new arr_type[n_col];
    }
}


void print_arr(arr_type** arr, int n_row, int n_col) {
    if (arr == nullptr) {
        std::cout << "Empty array";
        return;
    }

    for (int i = 0; i < n_row; ++i) {
        for (int j = 0; j < n_col; ++j) {
            std::cout << arr[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}


// сортировка пузырьком по первому элементу в строке
void sort_arr(arr_type** arr, int n_row) {
    for (int i = 0; i < n_row - 1; ++i) {
        for (int j = 0; j + 1 < n_row - i; ++j) {
            if (arr[j + 1][0] < arr[j][0]) {
                arr_type* tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

// случайный массив в определённом диапазоне
// используем &, чтобы можно было обратиться к arr и аллоцировать его
void create_random_arr(arr_type**& arr, int n_row, int n_col, arr_type min, arr_type max) {
    arr = new arr_type * [n_row];
    for (int i = 0; i < n_row; ++i) {
        arr[i] = new arr_type[n_col];
        for (int j = 0; j < n_col; ++j) {
            arr[i][j] = ((float)rand() / RAND_MAX) * (max - min) + min;
        }
    }
}



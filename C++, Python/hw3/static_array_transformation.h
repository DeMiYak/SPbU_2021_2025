#include "2d_dynamic_arr.h"
const int N_MAX = 100;

class string;

bool check_boundaries(long n_row, long n_col);
void change_min_and_max_rows(arr_type arr[N_MAX][N_MAX], int n_row, int n_col);
void print_arr(arr_type arr[N_MAX][N_MAX], int n_row, int n_col);
void delete_rows_like_first(arr_type arr[N_MAX][N_MAX], int& n_row, int n_col);
void read_arr_from_file(arr_type arr[N_MAX][N_MAX], int& n_row, int& n_col, const char*
	file_name);
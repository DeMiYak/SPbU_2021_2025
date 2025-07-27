#ifndef MATRIXOPER_H_INCLUDED
#define MATRIXOPER_H_INCLUDED

//Dyn
/*

matrixDyn *matrixDyn_sum(matrixDyn *m, const matrixDyn *m1, const matrixDyn *m2);

matrixDyn *matrixDyn_mult_scalar_row(matrixDyn *m, size_t i, double eps);

matrixDyn *matrixDyn_mult_scalar_column(matrixDyn *m, size_t j, double eps);

matrixDyn *matrixDyn_mult_scalar_all(matrixDyn *m, double eps);

matrixDyn *matrixDyn_substr(matrixDyn *m, const matrixDyn *m1, const matrixDyn *m2);

matrixDyn *matrixDyn_mult_matrixes(const matrixDyn *m1, const matrixDyn *m2);

matrixDyn *matrixDyn_add_row_scalar(matrixDyn *m, size_t i, size_t j, double eps);

matrixDyn *matrixDyn_swap_row(matrixDyn *m, size_t i, size_t j);

matrixDyn *matrixDyn_add(matrixDyn *m, const matrixDyn *m1);

matrixDyn *matrixDyn_transpose_square(matrixDyn *m);

matrixDyn *matrixDyn_transpose_rect(matrixDyn *m);

*/
//Line

matrixLine *matrixLine_sum(matrixLine *m, const matrixLine *m1, const matrixLine *m2);

matrixLine *matrixLine_mult_scalar_row(matrixLine *m, size_t i, double eps);

matrixLine *matrixLine_mult_scalar_column(matrixLine *m, size_t j, double eps);

matrixLine *matrixLine_mult_scalar_all(matrixLine *m, double eps);

matrixLine *matrixLine_substr(matrixLine *m, const matrixLine *m1, const matrixLine *m2);

matrixLine *matrixLine_mult_matrixes(const matrixLine *m1, const matrixLine *m2);

matrixLine *matrixLine_mult_matrixes_Taylor(const matrixLine *m1, const matrixLine *m2);

matrixLine *matrixLine_add_row_scalar(matrixLine *m, size_t i, size_t j, double eps);

matrixLine *matrixLine_swap_row(matrixLine *m, size_t i, size_t j);

matrixLine *matrixLine_add(matrixLine *m, const matrixLine *m1);

matrixLine *matrixLine_transpose_square(matrixLine *m);

matrixLine *matrixLine_transpose_rect(matrixLine *m);

#endif // MATRIXOPER_H_INCLUDED

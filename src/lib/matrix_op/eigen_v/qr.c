/**
    ANSI C standard: c11
    matrix_ejen_v.c
    Purpose: Module to get eigen values by QR Method

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdlib.h>

#include "numsys/matrix/matrixio.h"
#include "numsys/matrix/matrix.h"
#include "numsys/matrix_op/matrix_qr.h"

#define NS_EIGEN_V_QR_IMPORT
#define NS_EIGEN_V_QR_MAX_ITER 10000
#include "numsys/matrix_op/eigen_v/qr.h"


/*
    Compute the eigen vectors and eigen values with the QR Method
    Returns a matrix where the column i is the ith eigen vector
    The 'matrix' will contains the egein values
*/
NSMatrix matrix_eigen_qr_method(NSMatrix * matrix) {
    int rows = matrix->rows, cols = matrix->cols;
    NSMatrix * A = matrix;
    NSMatrix Q = matrixio_allocate_matrix(matrix->rows, matrix->cols);
    NSMatrix R = matrixio_allocate_matrix(matrix->cols, matrix->cols);

    for (int iter = 0; iter < NS_EIGEN_V_QR_MAX_ITER; iter++) {
        matrix_qr_decomposition(A, &R);
        NS_SWAP(Q.items, A->items, double **);
        matrix_multiply_mmd(R.items, Q.items, A->items, rows, cols, cols);
        if (matrix_verify_diagonal(*A) == NS__MATRIX_ERR_NONE__) break;
    }

    matrixio_free_matrix(&R);

    return Q;
}

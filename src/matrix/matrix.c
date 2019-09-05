/**
    ANSI C standard: c11
    matrix.cpp
    Purpose: Contains helper to create a liberate matrices dinamicly

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#define MATRIX_IMPORT
#include "matrix.h"

/* Find the max element into a matrix range */
MatrixElement matrix_find_max_element(double ** matrix, int from_row, int to_row, int from_col, int to_col) {
    MatrixElement mp;

    mp.value = matrix[from_row][from_col];
    mp.row = from_row;
    mp.col = from_col;

    for (int i = from_row; i < to_row; i++) {
        for (int j = from_col; j < to_col; j++) {
            if (ABS(matrix[i][j]) > ABS(mp.value)) {
                mp.value = matrix[i][j];
                mp.row = i;
                mp.col = j;
            }
        }
    }

    return mp;
}

/* Swap matrix columns */
void matrix_swap_cols(double **matrix, int col_size, int col_1, int col_2) {
    for (int i = 0; i < col_size; i++){
        SWAP(matrix[i][col_1], matrix[i][col_2], double);
    }
}

/* Swap matrix rows */
void matrix_swap_rows(double **matrix, int row_1, int row_2) {
    SWAP(matrix[row_1], matrix[row_2], double *);
}

/* Multiply matrix a x b and returns the values in a new matrix */
Matrix matrix_multiply(Matrix a, Matrix b) {
    Matrix result = matrixio_allocate(a.rows, b.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < b.cols; j++) {
            result.content[i][j] = 0.0;
            for (int k = 0; k < a.cols; k++) {
                result.content[i][j] += a.content[i][k] * b.content[k][j];
            }
        }
    }

    return result;
}

/* Verify that the matrix is a upper triangular matrix */
__flag_err matrix_verify_upper_triangular(Matrix matrix) {
    __flag_err flags = __MATRIX_ERR_NONE__;

    for (int i = 0; i < matrix.rows; i++) {
        if (IS_ZERO(matrix.content[i][i])) {
            flags |= __MATRIX_ERR_HAS_ZERO_ON_DIAG__;
        }
        for (int j = 0; j < i; j++) {
            if(!IS_ZERO(matrix.content[i][j])) {
                flags |= __MATRIX_ERR_NO_UPPER_TRIANGULAR__;
                return flags;
            }
        }
    }

    return flags;
}

/* Verify that the matrix is a lower triangular matrix */
__flag_err matrix_verify_lower_triangular(Matrix matrix) {
    __flag_err flags = __MATRIX_ERR_NONE__;

    for (int i = 0; i < matrix.rows; i++) {
        if (IS_ZERO(matrix.content[i][i])) {
            flags |= __MATRIX_ERR_HAS_ZERO_ON_DIAG__;
        }
        for (int j = i+1; j < matrix.cols; j++) {
            if(!IS_ZERO(matrix.content[i][j])) {
                flags |= __MATRIX_ERR_NO_LOWER_TRIANGULAR__;
                return flags;
            }
        }
    }

    return flags;
}

/* Verify that the matrix is a diagonal matrix */
__flag_err matrix_verify_diagonal(Matrix matrix) {
    __flag_err flags = __MATRIX_ERR_NONE__;

    flags |= matrix_verify_upper_triangular(matrix);
    flags |= matrix_verify_lower_triangular(matrix);

    if (!(!(flags & __MATRIX_ERR_NO_LOWER_TRIANGULAR__) &&
        !(flags & __MATRIX_ERR_NO_UPPER_TRIANGULAR__) &&
        !(flags & __MATRIX_ERR_HAS_ZERO_ON_DIAG__))) {
        flags |= __MATRIX_ERR_NO_DIAGONAL_MATRIX__;
    }

    return flags;
}

/* Verify that the matrix is a symmetry matrix */
__flag_err matrix_verify_symmetry(Matrix matrix) {
    __flag_err flags = __MATRIX_ERR_NONE__;

    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            if (matrix.content[i][j] != matrix.content[j][i]) {
                flags |= __MATRIX_ERR_NO_SYMMETRIC__;
                return flags;
            }
        }
    }

    return flags;
}

/* Verify that the matrix is a square matrix */
__flag_err matrix_check_dimensions(Matrix matrix) {
    __flag_err flags = __MATRIX_ERR_NONE__;

    if (matrix.rows != matrix.cols) {
        flags |= __MATRIX_ERR_NO_SQUARE_MATRIX__;
    }

    return flags;
}


/* Print the erros given by __flag_err */
void pmerror(char *prefix, __flag_err flags) {
    if (flags == 0) return;

    printf("Error: %s\n", prefix);

    if (flags & __MATRIX_ERR_NO_SOLUTION__) {
        puts(" - The matrix without unique solution");
    }
    if (flags & __MATRIX_ERR_NO_LU_DECOMPOSITION__) {
        puts(" - The matrix does not have LU decomposition");
    }
    if (flags & __MATRIX_ERR_NO_LDLT_DECOMPOSITION__) {
        puts(" - The matrix does not have LD(L-1) decomposition");
    }
    if (flags & __MATRIX_ERR_NO_UPPER_TRIANGULAR__) {
        puts(" - The matrix is not a upper triangular matrix");
    }
    if (flags & __MATRIX_ERR_NO_LOWER_TRIANGULAR__) {
        puts(" - The matrix is not a lower triangular matrix");
    }
    if (flags & __MATRIX_ERR_NO_DIAGONAL_MATRIX__) {
        puts(" - The matrix is not a diagonal matrix");
    }
    if (flags & __MATRIX_ERR_NO_SYMMETRIC__) {
        puts(" - The matrix is not a symmetric matrix");
    }
    if (flags & __MATRIX_ERR_HAS_ZERO_ON_DIAG__) {
        puts(" - The matrix has a zero over the diagonal");
    }
    if (flags & __MATRIX_ERR_NO_SQUARE_MATRIX__) {
        puts(" - The matrix is not a square matrix");
    }
    if (flags & __MATRIX_ERR_NO_INVERSE__) {
        puts(" - The matrix does not have inverse");
    }
}

/**
    ANSI C standard: c11
    matrix.cpp
    Purpose: Contains helper to create a liberate matrices dinamicly

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define MATRIX_IMPORT
#include "numsys/matrix/matrix.h"

/* Find the max element into a matrix range */
NSMatrixElem matrix_find_max_element(double ** matrix, int from_row, int to_row, int from_col, int to_col, NS__flag_ops ops) {
    NSMatrixElem mp = NSMatrixElemDefault;

    for (int i = from_row; i < to_row; i++) {
        for (int j = from_col; j < to_col; j++) {
            if (i == j && ops & NS__MATRIX_OPS_EXCLUDE_DIAG_) continue;

            if (NS_ABS(matrix[i][j]) > NS_ABS(mp.value)) {
                mp.value = matrix[i][j];
                mp.row = i;
                mp.col = j;
            }
        }
    }

    return mp;
}

/* Swap matrix columns */
void matrix_swap_cols(NSMatrix matrix, int col_1, int col_2) {
    for (int i = 0; i < matrix.rows; i++){
        NS_SWAP(matrix.items[i][col_1], matrix.items[i][col_2], double);
    }
}

/* Swap matrix rows */
void matrix_swap_rows(NSMatrix matrix, int row_1, int row_2) {
    NS_SWAP(matrix.items[row_1], matrix.items[row_2], double *);
}

/* Normalize a vector and returns the position the maximun element */
double matrix_normalize_v(double * vector, int size) {
    double norm = 0;

    double * vec_pos = vector;
    for (int i = 0; i < size; i++, vec_pos++) {
        norm += (*vec_pos) * (*vec_pos);
    }
    norm = sqrt(norm);

    vec_pos = vector;
    for (int i = 0; i < size; i++, vec_pos++) {
        *vec_pos /= norm;
    }

    return norm;
}

/* Randomnize a vector */
void matrix_randomnize_v(double * vector, int size) {
    srandom(time(NULL));

    for (int i = 0; i < size; i++, vector++) {
        *vector = (double) (random() % 100) + 1.0;
    }
}

/* Multiply matrix a x b = c and save the result in the matrix c */
void matrix_multiply_mmd(double ** a, double ** b, double ** c, int arows, int acols, int bcols) {
    double ** a_i = a;
    double ** b_i = b;
    double ** c_i = c;

    for (int i = 0; i < arows; i++, a_i++, b_i++, c_i++) {
        double ** b_k = b;
        double * a_ik = *a_i;
        memset(*c_i, 0, bcols * sizeof(double));
        for (int k = 0; k < acols; k++, a_ik++, b_k++) {
            double * b_kj = *b_k;
            double * c_ij = *c_i;
            for (int j = 0; j < bcols; j++, b_kj++, c_ij++) {
                *c_ij += (*a_ik) * (*b_kj);
            }
        }
    }
}

/* Multiply matrix a x b and returns the values in a new matrix */
NSMatrix matrix_multiply_mm(NSMatrix a, NSMatrix b) {
    NSMatrix result = matrixio_allocate_matrix(a.rows, b.cols);
    matrix_multiply_mmd(a.items, b.items, result.items, a.rows, a.cols, b.cols);
    return result;
}

/* Multiply a matrix 'a' and an array 'b' and save the result in the array 'c' */
void matrix_multiply_mvd(double ** a, double * b, double * c, int arows, int acols) {
    double ** a_i = a, * c_i = c;

    for (int i = 0; i < arows; i++, a_i++, c_i++) {
        double * b_j = b;
        double * a_ij = *a_i;

        *c_i = 0.0;
        for (int j = 0; j < acols; j++, b_j++, a_ij++) {
            *c_i += (*a_ij) * (*b_j);
        }
    }
}

/* Multiply a matrix 'a' and a vector 'b' and returns a new vector with the result */
NSVector matrix_multiply_mv(NSMatrix a, NSVector b) {
    NSVector result = matrixio_allocate_vector(b.size);
    matrix_multiply_mvd(a.items, b.items, result.items, a.rows, a.cols);
    return result;
}

/* Return a NSMatrix struct with that represents the identity */
NSMatrix matrix_create_identity(int size) {
    NSMatrix identity = matrixio_allocate_matrix(size, size);

    double ** idty_i = identity.items;
    for (int i = 0; i < size; i++, idty_i++) {
        (*idty_i)[i] = 1.0;
    }

    return identity;
}

/* Verify that the matrix is a upper triangular matrix */
NS__flag_err matrix_verify_upper_triangular(NSMatrix matrix) {
    NS__flag_err flags = NS__MATRIX_ERR_NONE__;

    for (int i = 0; i < matrix.rows; i++) {
        if (NS_IS_ZERO(matrix.items[i][i])) {
            flags |= NS__MATRIX_ERR_HAS_ZERO_ON_DIAG__;
        }
        for (int j = 0; j < i; j++) {
            if(!NS_IS_ZERO(matrix.items[i][j])) {
                flags |= NS__MATRIX_ERR_NO_UPPER_TRIANGULAR__;
                return flags;
            }
        }
    }

    return flags;
}

/* Verify that the matrix is a lower triangular matrix */
NS__flag_err matrix_verify_lower_triangular(NSMatrix matrix) {
    NS__flag_err flags = NS__MATRIX_ERR_NONE__;

    for (int i = 0; i < matrix.rows; i++) {
        if (NS_IS_ZERO(matrix.items[i][i])) {
            flags |= NS__MATRIX_ERR_HAS_ZERO_ON_DIAG__;
        }
        for (int j = i+1; j < matrix.cols; j++) {
            if(!NS_IS_ZERO(matrix.items[i][j])) {
                flags |= NS__MATRIX_ERR_NO_LOWER_TRIANGULAR__;
                return flags;
            }
        }
    }

    return flags;
}

/* Verify that the matrix is a diagonal matrix */
NS__flag_err matrix_verify_diagonal(NSMatrix matrix) {
    NS__flag_err flags = NS__MATRIX_ERR_NONE__;

    flags |= matrix_verify_upper_triangular(matrix);
    flags |= matrix_verify_lower_triangular(matrix);

    if (!(!(flags & NS__MATRIX_ERR_NO_LOWER_TRIANGULAR__) &&
        !(flags & NS__MATRIX_ERR_NO_UPPER_TRIANGULAR__) &&
        !(flags & NS__MATRIX_ERR_HAS_ZERO_ON_DIAG__))) {
        flags |= NS__MATRIX_ERR_NO_DIAGONAL_MATRIX__;
    }

    return flags;
}

/* Verify that the matrix is a symmetry matrix */
NS__flag_err matrix_verify_symmetry(NSMatrix matrix) {
    NS__flag_err flags = NS__MATRIX_ERR_NONE__;

    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            if (matrix.items[i][j] != matrix.items[j][i]) {
                flags |= NS__MATRIX_ERR_NO_SYMMETRIC__;
                return flags;
            }
        }
    }

    return flags;
}

/* Verify that the matrix is a square matrix */
NS__flag_err matrix_check_dimensions(NSMatrix matrix) {
    NS__flag_err flags = NS__MATRIX_ERR_NONE__;

    if (matrix.rows != matrix.cols) {
        flags |= NS__MATRIX_ERR_NO_SQUARE_MATRIX__;
    }

    return flags;
}


/* Print the erros given by NS__flag_err */
void nsperror(char *prefix, NS__flag_err flags) {
    if (flags == 0) return;

    printf("Error: %s\n", prefix);

    if (flags & NS__MATRIX_ERR_NO_SOLUTION__) {
        puts(" - The matrix without unique solution");
    }
    if (flags & NS__MATRIX_ERR_NO_LU_DECOMPOSITION__) {
        puts(" - The matrix does not have LU decomposition");
    }
    if (flags & NS__MATRIX_ERR_NO_LDLT_DECOMPOSITION__) {
        puts(" - The matrix does not have LD(L-1) decomposition");
    }
    if (flags & NS__MATRIX_ERR_NO_UPPER_TRIANGULAR__) {
        puts(" - The matrix is not a upper triangular matrix");
    }
    if (flags & NS__MATRIX_ERR_NO_LOWER_TRIANGULAR__) {
        puts(" - The matrix is not a lower triangular matrix");
    }
    if (flags & NS__MATRIX_ERR_NO_DIAGONAL_MATRIX__) {
        puts(" - The matrix is not a diagonal matrix");
    }
    if (flags & NS__MATRIX_ERR_NO_SYMMETRIC__) {
        puts(" - The matrix is not a symmetric matrix");
    }
    if (flags & NS__MATRIX_ERR_HAS_ZERO_ON_DIAG__) {
        puts(" - The matrix has a zero over the diagonal");
    }
    if (flags & NS__MATRIX_ERR_NO_SQUARE_MATRIX__) {
        puts(" - The matrix is not a square matrix");
    }
    if (flags & NS__MATRIX_ERR_NO_INVERSE__) {
        puts(" - The matrix does not have inverse");
    }
}

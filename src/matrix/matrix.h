/**
    ANSI C standard: c11
    matrix.cpp
    Purpose: Prototype for functions to make operations over a matrix

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#ifndef MATRIX_H
#define MATRIX_H

#include "matrixio.h"

#ifdef MATRIX_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

/* Generic swap */
#define SWAP(x, y) do { typeof(x) SWAP = x; x = y; y = SWAP; } while (0)

#define ABS(n) (((n) < 0)? -(n):(n))

static const int __ARCH_64__ = 64;
static const int __ARCH_32__ = 32;
static const int __ARCH__ = sizeof(void *) * 8;

/* Epsilon value */
static const double __EPSILON_64__ = 2.22045E-14; // 2.22045E-16 Real value
static const double __EPSILON_32__ = 1.0842E-17; // 1.0842E-19 Real Value

#define __EPSILON__ (__ARCH__ == __ARCH_64__)? __EPSILON_64__ : __EPSILON_32__
#define IS_ZERO(n) ((ABS(n) < __EPSILON__)? 1:0)

/*
    Flags to modify matrix operations or process
*/
typedef unsigned long int __flag_ops;
static const __flag_ops __MATRIX_OPS_NONE_ = 0;
static const __flag_ops __MATRIX_OPS_DIAG_HAS_ONES__ = 1;

/* Flags to track state and information about the matrix*/
typedef unsigned long int __flag_err;
static const __flag_err __MATRIX_ERR_NONE__ = 0;
static const __flag_err __MATRIX_ERR_NO_SOLUTION__ = 1;
static const __flag_err __MATRIX_ERR_NO_LU_DECOMPOSITION__ = 1 << 1;
static const __flag_err __MATRIX_ERR_NO_LDLT_DECOMPOSITION__ = 1 << 2;
static const __flag_err __MATRIX_ERR_NO_UPPER_TRIANGULAR__ = 1 << 3;
static const __flag_err __MATRIX_ERR_NO_LOWER_TRIANGULAR__ = 1 << 4;
static const __flag_err __MATRIX_ERR_NO_DIAGONAL_MATRIX__ = 1 << 5;
static const __flag_err __MATRIX_ERR_NO_SIMETRIC__ = 1 << 6;
static const __flag_err __MATRIX_ERR_HAS_ZERO_ON_DIAG__ = 1 << 7;
static const __flag_err __MATRIX_ERR_NO_SQUARE_MATRIX__ = 1 << 8;
static const __flag_err __MATRIX_ERR_NO_INVERSE__ = 1 << 9;



/* Represent a matrix element with the positions i,j */
static const struct matrix_MatrixElement {
    double value;
    int row;
    int col;
} MatrixElementDefault = {0.0, 0, 0};

typedef struct matrix_MatrixElement MatrixElement;


/* Find the max element into a matrix range */
EXTERN MatrixElement matrix_find_max_element(double ** matrix, int from_row, int to_row, int from_col, int to_col);

/* Swap matrix columns */
EXTERN void matrix_swap_cols(double **matrix, int col_size, int col_1, int col_2);

/* Swap matrix rows */
EXTERN void matrix_swap_rows(double **matrix, int row_1, int row_2);

/* Multiply matrix a x b and returns the values in a new matrix */
EXTERN Matrix matrix_multiply_square_matrices(Matrix a, Matrix b);

/* Verify that the matrix is a upper triangular matrix */
EXTERN __flag_err matrix_is_upper_triangular(Matrix matrix);

/* Verify that the matrix is a lower triangular matrix */
EXTERN __flag_err matrix_is_lower_triangular(Matrix matrix);

/* Verify that the matrix is a diagonal matrix */
EXTERN __flag_err matrix_is_diagonal(Matrix matrix);

/* Verify that the matrix is a simetric matrix */
EXTERN __flag_err matrix_is_simetric(Matrix matrix);

/* Verify that the matrix is a square matrix */
EXTERN __flag_err matrix_is_square(Matrix matrix);


#undef MATRIX_IMPORT
#undef EXTERN
#endif

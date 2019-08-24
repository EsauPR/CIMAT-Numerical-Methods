/**
    ANSI C standard: c11
    matrix.cpp
    Purpose: Prototype for functions to make operations over a matrix

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#ifndef MATRIX_H
#define MATRIX_H

#ifdef MATRIX_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

/* Generic swap */
#define SWAP(x, y) do { typeof(x) SWAP = x; x = y; y = SWAP; } while (0)

#define ABS(n) (((n) < 0)? -(n):(n))

/* Epsilon value */
static const double EPSILON = 2.22045E-16;


/*
    Flags to modify matrix operations o process, state and information
*/
typedef unsigned char __flag_t;
static const unsigned char __MATRIX_NO_FLAGS__ = 0;
static const unsigned char __MATRIX_NO_STATE__ = __MATRIX_NO_FLAGS__;
static const unsigned char __MATRIX_DIAG_HAS_ONES__ = 1;
static const unsigned char __MATRIX_NO_INVERSE__ = 1 << 1;
static const unsigned char __MATRIX_NO_LU_DECOMPOSITION__ = 1 << 2;
static const unsigned char __MATRIX_NO_LDLT_DECOMPOSITION__ = 1 << 3;


/* Represent a matrix element with the positions i,j */
static const struct matrix_MatrixElement {
    double value;
    int row;
    int col;
} MatrixElementDefault = {0.0, 0, 0};

typedef struct matrix_MatrixElement MatrixElement;


/* Find the max element into a matrix range */
EXTERN MatrixElement find_matrix_max_element(double ** matrix, int from_row, int to_row, int from_col, int to_col);

/* Swap matrix columns */
EXTERN void swap_matrix_cols(double **matrix, int col_size, int col_1, int col_2);

/* Swap matrix rows */
EXTERN void swap_matrix_rows(double **matrix, int row_1, int row_2);

#undef MATRIX_IMPORT
#undef EXTERN
#endif

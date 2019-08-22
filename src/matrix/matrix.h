/**
    ANSI C standard: c11
    matrix.cpp
    Purpose: Prototype for functions to make operations over a matrix

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#ifndef MATRIX_H
#define MATRIX_H

#include "../linear_equations_systems_solutions/solution.h"

#ifdef MATRIX_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

/* Generic swap */
#define SWAP(x, y) do { typeof(x) SWAP = x; x = y; y = SWAP; } while (0)

#define ABS(n) (((n) < 0)? -(n):(n))


/*
    Falgs to make operations
*/
typedef unsigned char __flag_t;
static const unsigned char __NO_MATRIX_FLAGS__ = 0;
static const unsigned char __DIAGONAL_HAS_ONES__ = 1;


/* Represent a matrix element with the positions i,j */
typedef struct matrix_MatrixElement{
    double value;
    int row;
    int col;
} MatrixElement;


/* Find the max element into a matrix range */
EXTERN MatrixElement find_matrix_max_element(double ** matrix, int from_row, int to_row, int from_col, int to_col);

/* Swap matrix columns */
EXTERN void swap_matrix_cols(double **matrix, int col_size, int col_1, int col_2);

/* Swap matrix rows */
EXTERN void swap_matrix_rows(double **matrix, int row_1, int row_2);

/*
    Make a LU decomposition over the same matrix. L is a lower trangular matrix
    with ones over the diagonal.

    You must asume that the diagonal is ones for L and the values already computed for U

    Returns the determinant for U
*/
EXTERN SystemSolution LU_decomposition(double ** matrix, int size);

#undef MATRIX_IMPORT
#undef EXTERN
#endif

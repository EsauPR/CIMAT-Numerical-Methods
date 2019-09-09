/**
    ANSI C standard: c11
    matrix.cpp
    Purpose: Prototype for functions to make operations over a matrix

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>
#include "numsys/matrix/matrixio.h"

#ifdef MATRIX_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

/* Find the max element into a matrix range */
EXTERN NSMatrixElem matrix_find_max_element(double ** matrix, int from_row, int to_row, int from_col, int to_col);

/* Swap matrix columns */
EXTERN void matrix_swap_cols(NSMatrix matrix, int col_1, int col_2);

/* Swap matrix rows */
EXTERN void matrix_swap_rows(NSMatrix matrix, int row_1, int row_2);

/* Multiply matrix a x b and returns the values in a new matrix */
EXTERN NSMatrix matrix_multiply(NSMatrix a, NSMatrix b);

/* Verify that the matrix is a upper triangular matrix */
EXTERN NS__flag_err matrix_verify_upper_triangular(NSMatrix matrix);

/* Verify that the matrix is a lower triangular matrix */
EXTERN NS__flag_err matrix_verify_lower_triangular(NSMatrix matrix);

/* Verify that the matrix is a diagonal matrix */
EXTERN NS__flag_err matrix_verify_diagonal(NSMatrix matrix);

/* Verify that the matrix is a symmetry matrix */
EXTERN NS__flag_err matrix_verify_symmetry(NSMatrix matrix);

/* Verify that the matrix is a square matrix */
EXTERN NS__flag_err matrix_check_dimensions(NSMatrix matrix);

/* Print the erros given by NS__flag_err */
EXTERN void nsperror(char *prefix, NS__flag_err flags);


#undef MATRIX_IMPORT
#undef EXTERN
#endif

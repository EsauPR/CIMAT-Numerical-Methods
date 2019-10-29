/**
    ANSI C standard: c11
    matrix.cpp
    Purpose: Prototype for functions to make operations over a matrix

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#ifndef MATRIX_SPARSE_H
#define MATRIX_SPARSE_H

#include <stddef.h>

#include "numsys/matrix/matrix_core.h"
#include "numsys/matrix/matrixio.h"
#include "numsys/matrix/matrix.h"


#ifdef MATRIX_SPARSE_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

EXTERN NSMatrixSparse matrix_sparse_create(int max, int rows, int cols);

EXTERN void matrix_sparse_insert(NSMatrixSparse * matrix, int row, int col, double value);

EXTERN void matrix_sparse_add(NSMatrixSparse * A, NSMatrixSparse * B, NSMatrixSparse * C);

EXTERN void matrix_sparse_transpose(NSMatrixSparse * matrix, NSMatrixSparse * transpose);

EXTERN void matrix_sparse_multiply(NSMatrixSparse * A, NSMatrixSparse * B, NSMatrixSparse * C);

EXTERN void matrix_sparse_show(NSMatrixSparse matrix);

EXTERN void matrix_sparse_free(NSMatrixSparse * matrix);

EXTERN int matrix_sparse_find_value(NSMatrixSparse matrix, int row, int col, double * result);


#undef NSMATRIX_CORE_IMPORT
#undef EXTERN
#endif

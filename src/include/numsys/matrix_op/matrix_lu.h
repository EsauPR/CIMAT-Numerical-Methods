/**
    ANSI C standard: c11
    matrix.cpp
    Purpose: Prototype for functions to make operations over a matrix

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#ifndef MATRIX_LU_H
#define MATRIX_LU_H

#include "numsys/solvers/solution.h"

#ifdef MATRIX_LU_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif


/*
    Make a LU decomposition over the same matrix. L is a lower trangular matrix
    with ones over the diagonal.

    You must asume that the diagonal is ones for L and the values already computed for U

    Returns the determinant for U
*/
EXTERN SystemSolution matrix_lu_decomposition(double ** matrix, int size);

#undef MATRIX_LU_IMPORT
#undef EXTERN
#endif

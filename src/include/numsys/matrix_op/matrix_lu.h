/**
    ANSI C standard: c11
    matrix.cpp
    Purpose: Prototype for functions to make operations over a matrix

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#ifndef MATRIX_LU_H
#define MATRIX_LU_H

#include "numsys/matrix/matrix_core.h">

#ifdef MATRIX_LU_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif


/*
    Make a LU decomposition over the same matrix. L is a lower trangular matrix
    with ones over the diagonal.

    You must asume that the diagonal is ones for L and the values already computed for

    Returns a vector with the mapping for rows permutations with size matrix.rows
*/
EXTERN int * matrix_lu_decomposition(NSMatrix * matrix);

#undef MATRIX_LU_IMPORT
#undef EXTERN
#endif

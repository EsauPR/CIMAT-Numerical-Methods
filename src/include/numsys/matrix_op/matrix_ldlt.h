/**
    ANSI C standard: c11
    matrix.cpp
    Purpose: Prototype for functions to make operations over a matrix

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#ifndef MATRIX_LDLT_H
#define MATRIX_LDLT_H

#include "numsys/matrix/matrix_core.h"

#ifdef MATRIX_LDLT_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif


/*
    Make a LDLt decomposition over the same matrix. L is a lower trangular matrix
    with ones over the diagonal.

    You must asume that the diagonal is ones for L and the values already computed for D

    Returns the rows permutation mapping
*/
EXTERN int * matrix_ldlt_decomposition(NSMatrix * matrix);

#undef MATRIX_LDLT_IMPORT
#undef EXTERN
#endif

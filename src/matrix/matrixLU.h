/**
    ANSI C standard: c11
    matrix.cpp
    Purpose: Prototype for functions to make operations over a matrix

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#ifndef MATRIXLU_H
#define MATRIXLU_H

#include "../linear_equations_systems_solutions/solution.h"

#ifdef MATRIXLU_IMPORT
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
EXTERN SystemSolution LU_decomposition(double ** matrix, int size);

#undef MATRIXLU_IMPORT
#undef EXTERN
#endif

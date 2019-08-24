/**
    ANSI C standard: c11
    matrix.cpp
    Purpose: Prototype for functions to make operations over a matrix

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#ifndef MATRIXLUDLT_H
#define MATRIXLUDLT_H

#include "../linear_equations_systems_solutions/solution.h"

#ifdef MATRIXLUDLT_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif


/*
    Make a LDLt decomposition over the same matrix. L is a lower trangular matrix
    with ones over the diagonal.

    You must asume that the diagonal is ones for L and the values already computed for D

    Returns the determinant for U
*/
EXTERN SystemSolution LDLt_decomposition(double ** matrix, int size);

#undef MATRIXLUDLT_IMPORT
#undef EXTERN
#endif

/**
    ANSI C standard: c11
    jacobi.c
    Purpose: Prototype for module to get eigen vectors and
    eigen values by SUBSPACE_ITERATION Algorithm

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#ifndef NS_EIGEN_V_SUBSPACE_ITERATION_H
#define NS_EIGEN_V_SUBSPACE_ITERATION_H

#include "numsys/matrix/matrix_core.h"

#ifdef NS_EIGEN_V_SUBSPACE_ITERATION_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

/*
    Compute the n eigen vectors and eigen values with the Subspace Iteration Method
    A will be reduced to a matrix that contains the eigen values
    Returns a matrix where each column is a eigen vector
*/
EXTERN NSMatrix matrix_eigen_subspace_iteration_method(NSMatrix * matrix, int neigen);

#undef NS_EIGEN_V_SUBSPACE_ITERATION_IMPORT
#undef EXTERN
#endif

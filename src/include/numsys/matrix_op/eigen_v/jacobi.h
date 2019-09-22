/**
    ANSI C standard: c11
    jacobi.c
    Purpose: Prototype for module to get eigen vetors and eigen values
    with Jacobi Method

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#ifndef NSEigenV_JACOBI_H
#define NSEigenV_JACOBI_H

#include "numsys/matrix/matrix_core.h"

#ifdef NSEigenV_JACOBI_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

/*
    Compute the eigen vectors and eigen values with the Jacobi method
    Returns a matrix where the column i is the ith eigen vector
    The 'matrix' will contains the egein values
*/
EXTERN NSMatrix matrix_eigen_jacobi_method(NSMatrix * matrix);

#undef NSEigenV_JACOBI_IMPORT
#undef EXTERN
#endif

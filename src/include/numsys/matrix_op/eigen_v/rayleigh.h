/**
    ANSI C standard: c11
    jacobi.c
    Purpose: Prototype for module to get eigen vetors and
    eigen values with Rayleigh Method

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#ifndef NSEigenV_RAYLEIGH_H
#define NSEigenV_RAYLEIGH_H

#include "numsys/matrix/matrix_core.h"

#ifdef NSEigenV_RAYLEIGH_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

/*
    Compute the eigen vectors and eigen values with the Rayleigh Method
    Returns a matrix where the column i is the ith eigen vector
    The 'matrix' will contains the egein values
*/
EXTERN void matrix_eigen_rayleigh_method(NSMatrix * matrix, NSEigenV * eigenv);

#undef NSEigenV_RAYLEIGH_IMPORT
#undef EXTERN
#endif

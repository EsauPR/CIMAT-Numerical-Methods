/**
    ANSI C standard: c11
    matrix_ejen_v.h
    Purpose: Prototype for module to get eigen vetors
    and eigen values with the pow method

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#ifndef NSEigenV_H
#define NSEigenV_H

#include "numsys/matrix/matrix_core.h"

#ifdef NSEigenV_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

/* Compute the min eigen value and their eigen vector through the pow method*/
EXTERN NSEigenV matrix_eigen_pow_method(NSMatrix * matrix);

/* Compute the min eigen value and their eigen vector through the inverse pow method*/
EXTERN NSEigenV matrix_eigen_pow_method_inv(NSMatrix * matrix);

/*
    Compute the n eigen values and their eigen vectors through
    deflation process with the pow method
*/
EXTERN NSEigenV * matrix_eigen_pow_method_dfl(NSMatrix * matrix, const int neigen);

/*
    Compute the n eigen values and their eigen vectors through
    deflation process with the inverse pow method
*/
EXTERN NSEigenV * matrix_eigen_pow_method_inv_dfl(NSMatrix * matrix, const int neigen);

/* Free NSEigenV struct */
EXTERN void matrixio_free_eigen_v(NSEigenV * eigen_v);


#undef NSEigenV_IMPORT
#undef EXTERN
#endif

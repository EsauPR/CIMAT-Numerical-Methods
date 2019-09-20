/**
    ANSI C standard: c11
    jacobi.c
    Purpose: Prototype for module to get eigen vectors and
    eigen values by QR Algorithm

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#ifndef NS_EIGEN_V_QR_H
#define NS_EIGEN_V_QR_H

#include "numsys/matrix/matrix_core.h"

#ifdef NS_EIGEN_V_QR_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

/*
    Compute the eigen vectors and eigen values with the QR Method
    Returns a matrix where the column i is the ith eigen vector
    The 'matrix' will contains the egein values
*/
EXTERN NSMatrix matrix_eigen_qr_method(NSMatrix * matrix);

#undef NS_EIGEN_V_QR_IMPORT
#undef EXTERN
#endif

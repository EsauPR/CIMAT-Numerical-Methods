/**
    ANSI C standard: c11
    matrix.cpp
    Purpose: Prototype for functions to make QR Factorization

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#ifndef MATRIX_QR_H
#define MATRIX_QR_H

#include "numsys/matrix/matrix_core.h"

#ifdef MATRIX_QR_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif


/*
    Make a QR decomposition of a matrix 'A'
    The matrix 'R' will contain the values for R
    and A will contain the values for 'Q'
*/
EXTERN void matrix_qr_decomposition(NSMatrix * A, NSMatrix * R);

#undef MATRIX_QR_IMPORT
#undef EXTERN
#endif

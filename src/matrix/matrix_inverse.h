/**
    ANSI C standard: c11
    matrix.cpp
    Purpose: Prototype for functions to make operations over a matrix

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#ifndef MATRIX_INVERSE_H
#define MATRIX_INVERSE_H

#include "../matrix/matrixio.h"

#ifdef MATRIX_INVERSE_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif


/* Compute the matrix inverse with LU factorization */
EXTERN Matrix matrix_inverse_get(Matrix matrix);

#undef MATRIX_INVERSE_IMPORT
#undef EXTERN
#endif

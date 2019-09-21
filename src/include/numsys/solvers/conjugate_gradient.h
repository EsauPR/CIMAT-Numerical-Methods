/**
    ANSI C standard: c11
    jacobi.c
    Purpose: Prototype for Conjugate Gradiente Method

   @author Esaú Peralta
   @email esau.opr@gmail.com
*/

#ifndef CONJ_GRADIENT_H
#define CONJ_GRADIENT_H

#include "numsys/matrix/matrixio.h"

#ifdef CONJ_GRADIENT_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

/* Solve a square symmetric matrix by Conjugate Gradient Method */
EXTERN void conjugate_gradient_solver(NSMatrixSystem * msystem);

#undef CONJ_GRADIENT_IMPORT
#undef EXTERN
#endif

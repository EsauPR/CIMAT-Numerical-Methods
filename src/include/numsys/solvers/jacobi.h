/**
    ANSI C standard: c11
    jacobi.c
    Purpose: Prototype for Jacobi iterative method

   @author Esaú Peralta
   @email esau.opr@gmail.com
*/

#ifndef JACOBI_H
#define JACOBI_H

#include "numsys/matrix/matrixio.h"

#ifdef JACOBI_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

/* Solve a square matrix by Jacobi iterative method */
EXTERN void jacobi_solver(NSMatrixSystem * msystem);

#undef JACOBI_IMPORT
#undef EXTERN
#endif

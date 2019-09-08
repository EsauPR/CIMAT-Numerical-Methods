/**
    ANSI C standard: c11
    jacobi.c
    Purpose: Prototype for Gauss Seidel iterative method

   @author Esaú Peralta
   @email esau.opr@gmail.com
*/

#ifndef GAUSS_SEIDEL_H
#define GAUSS_SEIDEL_H

#include "numsys/matrix/matrixio.h"

#ifdef GAUSS_SEIDEL_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

/* Solve a square matrix by Gauss Seidel iterative method */
EXTERN void gauss_seidel_solver(NSMatrixSystem * msystem);

#undef GAUSS_SEIDEL_IMPORT
#undef EXTERN
#endif

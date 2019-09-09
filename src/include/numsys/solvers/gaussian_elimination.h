/**
    ANSI C standard: c11
    gaussian_elimination.c
    Purpose: Prototype implementation for guassian elimination algorithm

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#ifndef GAUSSIAN_ELIMINATION_H
#define GAUSSIAN_ELIMINATION_H

#include "numsys/matrix/matrixio.h"

#ifdef GAUSSIAN_ELIMINATION_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

/* Solve a square matrix by gaussian elimination without pivot */
EXTERN void solver_gaussian_elimination_simple(NSMatrixSystem * msystem);

/* Solve a square matrix by gaussian elimination with pivot */
EXTERN void solver_gaussian_elimination(NSMatrixSystem * msystem);


#endif

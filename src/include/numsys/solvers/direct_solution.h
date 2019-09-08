/**
    ANSI C standard: c11
    direct_solution.c
    Purpose: Prototype implementation for a direct solution when the matrix is
    a diagonal matrix

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#ifndef DIRECT_SOLUTION_H
#define DIRECT_SOLUTION_H

#include "numsys/matrix/matrixio.h"

#ifdef DIRECT_SOLUTION_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif


/* Solver for a diagonal matrix */
EXTERN void solver_diagonal_matrix(NSMatrixSystem * msystem);

#undef DIRECT_SOLUTION_IMPORT
#undef EXTERN
#endif

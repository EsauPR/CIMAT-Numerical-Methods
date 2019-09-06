/**
    ANSI C standard: c11
    {file}.c
    Purpose: {Description}

   @author Esaú Peralta
   @email esau.opr@gmail.com
*/

#ifndef CHOLESKY_H
#define CHOLESKY_H

#include "numsys/matrix/matrixio.h"
#include "numsys/solvers/solution.h"

#ifdef CHOLESKY_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

/* Solve a square matrix by Cholesky method */
EXTERN SystemSolution solve_by_cholesky_method(AugmentedMatrix matrix);

#undef CHOLESKY_IMPORT
#undef EXTERN
#endif

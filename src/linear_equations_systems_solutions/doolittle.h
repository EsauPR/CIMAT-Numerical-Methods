/**
    ANSI C standard: c11
    {file}.c
    Purpose: {Description}

   @author Esaú Peralta
   @email esau.opr@gmail.com
*/

#ifndef DOOLITTLE_H
#define DOOLITTLE_H

#include "../matrix/matrixio.h"
#include "solution.h"

#ifdef DOOLITTLE_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

/* Solve a LUx=B, the matrix must be a LU matrix */
EXTERN SystemSolution doolittle_method_solve_lu(AugmentedMatrix lu_matrix);

/* Solve a square matrix by Doolittle method */
EXTERN SystemSolution doolittle_method_solver(AugmentedMatrix matrix);

#undef DOOLITTLE_IMPORT
#undef EXTERN
#endif

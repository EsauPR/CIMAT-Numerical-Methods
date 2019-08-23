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

/* Solve a square matrix by Doolittle method */
EXTERN SystemSolution solve_by_doolittle_method(AugmentedMatrix matrix);

#undef DOOLITTLE_IMPORT
#undef EXTERN
#endif

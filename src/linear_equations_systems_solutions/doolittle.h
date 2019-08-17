/**
    ANSI C standard: c11
    {file}.c
    Purpose: {Description}

   @author Esaú Peralta
   @email esau.opr@gmail.com
*/

#ifndef DOOLITTLE_H
#define DOOLITTLE_H

#include "solution.h"

#ifdef DOOLITTLE_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

/* Solve a square matrix by gaussian elimination with pivot */
EXTERN SystemSolution solve_by_doolittle_method(double **matrix, int size);

#undef DOOLITTLE_IMPORT
#undef EXTERN
#endif

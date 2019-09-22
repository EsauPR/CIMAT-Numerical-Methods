/**
    ANSI C standard: c11
    {file}.c
    Purpose: {Description}

   @author Esaú Peralta
   @email esau.opr@gmail.com
*/

#ifndef DOOLITTLE_H
#define DOOLITTLE_H

#include "numsys/matrix/matrixio.h"

#ifdef DOOLITTLE_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

/* Solve a LUx=B, the matrix must be a LU matrix */
EXTERN void solver_doolittle_method_lu(NSMatrixSystem * msystem);

/* Solve a square matrix by Doolittle method */
EXTERN void solver_doolittle_method(NSMatrixSystem * msystem);

#undef DOOLITTLE_IMPORT
#undef EXTERN
#endif

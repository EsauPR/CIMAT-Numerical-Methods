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

#ifdef CHOLESKY_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

/* Solve a square matrix by Cholesky method */
EXTERN void solver_cholesky_method(NSMatrixSystem * msystem);

#undef CHOLESKY_IMPORT
#undef EXTERN
#endif

/**
    ANSI C standard: c11
    BWFW_SUBSTITUTION.h
    Purpose: Prototype for implementation for backward substitution algorithms

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#ifndef BWFW_SUBSTITUTION_H
#define BWFW_SUBSTITUTION_H

#include "numsys/matrix/matrixio.h"
#include "numsys/matrix/matrix.h"

#ifdef BWFW_SUBSTITUTION_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif


/*
    Return array with the solution for a lower triangular matrix
    using forward substitution

    Use the flag 'NS__MATRIX_OPS_DIAG_HAS_ONES__' to asume that the diagonal is fullfiled with ones
*/
EXTERN void solver_forward_substitution(NSMatrixSystem * msystem, NS__flag_ops flags);

/*
    Return array with the solution for a upper triangular matrix
    using backward substitution

    Use the flag 'NS__MATRIX_OPS_DIAG_HAS_ONES__' to asume that the diagonal is fullfiled with ones
*/
EXTERN void solver_backward_substitution(NSMatrixSystem * msystem, NS__flag_ops flags);

#undef BWFW_SUBSTITUTION_IMPORT
#undef EXTERN
#endif

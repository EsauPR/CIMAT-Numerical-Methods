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
#include "numsys/solvers/solution.h"

#ifdef BWFW_SUBSTITUTION_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif


/*
    Return array with the solution for a lower triangular matrix
    using backward substitution

    Use the flag '__MATRIX_OPS_DIAG_HAS_ONES__' to asume that the diagonal is fullfiled with ones
*/
EXTERN SystemSolution solve_lower_triangular_matrix(AugmentedMatrix, __flag_ops flags);

/*
    Return array with the solution for a upper triangular matrix
    using backward substitution

    Use the flag '__MATRIX_OPS_DIAG_HAS_ONES__' to asume that the diagonal is fullfiled with ones
*/
EXTERN SystemSolution solve_upper_triangular_matrix(AugmentedMatrix, __flag_ops flags);

#undef BWFW_SUBSTITUTION_IMPORT
#undef EXTERN
#endif

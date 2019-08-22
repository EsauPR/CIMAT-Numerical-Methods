/**
    ANSI C standard: c11
    BACKWARD_SUBSTITUTION.h
    Purpose: Prototype for implementation for backward substitution algorithms

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#ifndef BACKWARD_SUBSTITUTION_H
#define BACKWARD_SUBSTITUTION_H

#include "solution.h"

#ifdef BACKWARD_SUBSTITUTION_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif


/*
    Return array with the solution for a lower triangular matrix
    using backward substitution

    Use the flag 'diag_with_ones' to asume that the diagonal is fullfiled with ones
*/
EXTERN SystemSolution solve_lower_triangular_matrix(AugmentedMatrix, __flag_t flags);

/*
    Return array with the solution for a upper triangular matrix
    using backward substitution

    Use the flag 'diag_with_ones' to asume that the diagonal is fullfiled with ones
*/
EXTERN SystemSolution solve_upper_triangular_matrix(AugmentedMatrix, __flag_t flags);

#undef BACKWARD_SUBSTITUTION_IMPORT
#undef EXTERN
#endif

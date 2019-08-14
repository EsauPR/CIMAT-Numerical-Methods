/**
    ANSI C standard: c11
    backward_substitutions.h
    Purpose: Prototype for implementation for backward substitution algorithms

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#ifndef backward_substitutions_H
#define backward_substitutions_H

#ifdef backward_substitution_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif


/*
    Return array with the solution for a lower triangular matrix
    using backward substitution

*/
EXTERN double *solve_lower_triangular_matrix(double **matrix, int size);

/*
    Return array with the solution for a upper triangular matrix
    using backward substitution
*/
EXTERN double *solve_upper_triangular_matrix(double **matrix, int size);

#undef backward_substitution_IMPORT
#undef EXTERN
#endif

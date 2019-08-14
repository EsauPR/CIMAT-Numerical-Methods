/**
    ANSI C standard: c11
    BACKWARD_SUBSTITUTION.h
    Purpose: Prototype for implementation for backward substitution algorithms

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#ifndef BACKWARD_SUBSTITUTION_H
#define BACKWARD_SUBSTITUTION_H

#ifdef BACKWARD_SUBSTITUTION_IMPORT
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

#undef BACKWARD_SUBSTITUTION_IMPORT
#undef EXTERN
#endif

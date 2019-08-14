/**
    ANSI C standard: c11
    direct_solution.c
    Purpose: Prototype implementation for a direct solution when the matrix is
    a diagonal matrix

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#ifndef DIRECT_SOLUTION_H
#define DIRECT_SOLUTION_H

#ifdef DIRECT_SOLUTION_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif


/* Return array with the solution for a diagonal matrix */
EXTERN double *solve_diagonal_matrix(double **matrix, int size);

#undef DIRECT_SOLUTION_IMPORT
#undef EXTERN
#endif

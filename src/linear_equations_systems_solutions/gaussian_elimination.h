/**
    ANSI C standard: c11
    gaussian_elimination.c
    Purpose: Prototype implementation for guassian elimination algorithm

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#ifndef GAUSSIAN_ELIMINATION_H
#define GAUSSIAN_ELIMINATION_H

#include "solution.h"

#ifdef GAUSSIAN_ELIMINATION_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

/* Solve a square matrix by gaussian elimination without pivot */
EXTERN SystemSolution solve_by_simple_gaussian_elimination(double **matrix, int size);

/* Solve a square matrix by gaussian elimination with pivot */
EXTERN SystemSolution solve_by_gaussian_elimination(double **matrix, int size);


#endif

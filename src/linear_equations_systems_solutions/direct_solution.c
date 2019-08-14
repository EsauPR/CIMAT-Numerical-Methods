/**
    ANSI C standard: c11
    direct_solution.c
    Purpose: Implementation for a direct solution when the matrix is
    a diagonal matrix

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#include <stdio.h>
#include "../matrix.h"

#define DIRECT_SOLUTION_IMPORT
#include "direct_solution.h"

/* Return array with the solution for a diagonal matrix */
double *solve_diagonal_matrix(double **matrix, int size) {
    double * result = create_dynamic_array(size);
    for (int i = 0; i < size; i++) {
        result[i] = matrix[i][size] / matrix[i][i];
    }

    return result;
}

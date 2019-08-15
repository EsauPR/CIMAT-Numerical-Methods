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
SystemSolution solve_diagonal_matrix(double **matrix, int size) {
    SystemSolution system_solution;
    system_solution.solution = create_dynamic_array(size);
    system_solution.size = size;
    system_solution.determinat = 1.0;

    for (int i = 0; i < size; i++) {
        system_solution.solution[i] = matrix[i][size] / matrix[i][i];
        system_solution.determinat *= matrix[i][i];
    }

    return system_solution;
}

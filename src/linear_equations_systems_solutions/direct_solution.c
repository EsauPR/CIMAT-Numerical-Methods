/**
    ANSI C standard: c11
    direct_solution.c
    Purpose: Implementation for a direct solution when the matrix is
    a diagonal matrix

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#define DIRECT_SOLUTION_IMPORT
#include "direct_solution.h"

/* Return array with the solution for a diagonal matrix */
SystemSolution solve_diagonal_matrix(AugmentedMatrix matrix) {
    double ** mtx = matrix.content;
    int size = matrix.rows;

    SystemSolution system_solution = SystemSolutionDefault;
    system_solution.solution = allocate_double_array(size);
    system_solution.size = size;
    system_solution.determinant = 1.0;

    for (int i = 0; i < size; i++) {
        system_solution.solution[i] = mtx[i][size] / mtx[i][i];
        system_solution.determinant *= mtx[i][i];
    }

    return system_solution;
}

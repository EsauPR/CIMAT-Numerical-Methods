/**
    ANSI C standard: c11
    {file}.c
    Purpose: {Description}

   @author Esaú Peralta
   @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>

#include "../matrix/matrixio.h"
#include "../matrix/matrix.h"
#include "../linear_equations_systems_solutions/backward_substitution.h"

#define DOOLITTLE_IMPORT
#include "doolittle.h"


SystemSolution solve_by_doolittle_method(double **matrix, int size) {
    SystemSolution system_solution = LU_decomposition(matrix, size);
    if (system_solution.size == -1) {
        return system_solution;
    }
    // Solve Ly = b
    double diagonal_backup[size];
    for (int i = 0; i < size; i++) {
        diagonal_backup[i] = matrix[i][i];
        matrix[i][i] = 1.0;
    }
    system_solution.solution = solve_lower_triangular_matrix(matrix, size).solution;

    // Solve Ux = y
    for (int i = 0; i < size; i++) {
        matrix[i][i] = diagonal_backup[i];
        matrix[i][size] = system_solution.solution[i];
    }
    free(system_solution.solution);
    system_solution.solution = solve_upper_triangular_matrix(matrix, size).solution;

    return system_solution;
}

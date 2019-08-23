/**
    ANSI C standard: c11
    {file}.c
    Purpose: {Description}

   @author Esaú Peralta
   @email esau.opr@gmail.com
*/

#include <stdlib.h>
#include "../matrix/matrixLU.h"
#include "../linear_equations_systems_solutions/backward_substitution.h"

#define DOOLITTLE_IMPORT
#include "doolittle.h"


SystemSolution solve_by_doolittle_method(AugmentedMatrix matrix) {
    int size = matrix.rows;
    double **mtxc = matrix.content;

    SystemSolution system_solution = LU_decomposition(mtxc, size);
    if (system_solution.size == -1) {
        return system_solution;
    }

    // Solve Ly = b where L has a diagonal with ones
    system_solution.solution = solve_lower_triangular_matrix(matrix, __DIAGONAL_HAS_ONES__).solution;

    // Solve Ux = y
    for (int i = 0; i < size; i++) {
        mtxc[i][size] = system_solution.solution[i];
    }
    free(system_solution.solution);
    system_solution.solution = solve_upper_triangular_matrix(matrix, __NO_MATRIX_FLAGS__).solution;

    return system_solution;
}

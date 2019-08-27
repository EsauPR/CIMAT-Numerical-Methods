/**
    ANSI C standard: c11
    {file}.c
    Purpose: {Description}

   @author Esaú Peralta
   @email esau.opr@gmail.com
*/

#include <stdlib.h>
#include "../matrix/matrix_lu.h"
#include "../linear_equations_systems_solutions/backward_substitution.h"

#define DOOLITTLE_IMPORT
#include "doolittle.h"


SystemSolution solve_by_doolittle_method(AugmentedMatrix matrix) {
    int size = matrix.rows;
    double **mtxc = matrix.content;

    SystemSolution system_solution = matrix_lu_decomposition(mtxc, size);
    if (system_solution.err) {
        system_solution.err |= __MATRIX_ERR_NO_SOLUTION__;
        return system_solution;
    }
    double determinant = system_solution.determinant;
    solution_free(system_solution);

    // Solve Ly = b where L has a diagonal with ones
    system_solution = solve_lower_triangular_matrix(matrix, __MATRIX_OPS_DIAG_HAS_ONES__);

    // Solve Ux = y
    for (int i = 0; i < size; i++) {
        mtxc[i][size] = system_solution.solution[i];
    }
    solution_free(system_solution);
    system_solution = solve_upper_triangular_matrix(matrix, __MATRIX_OPS_NONE_);

    system_solution.determinant = determinant;
    return system_solution;
}

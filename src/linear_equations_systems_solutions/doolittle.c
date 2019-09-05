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


/* Solve a LUx=B, the matrix must be a LU matrix */
SystemSolution doolittle_method_solve_lu(AugmentedMatrix lu_matrix) {
    int size = lu_matrix.rows;
    // Solve Ly = b where L has a diagonal with ones
    SystemSolution system_solution = SystemSolutionDefault;
    system_solution = solve_lower_triangular_matrix(lu_matrix, __MATRIX_OPS_DIAG_HAS_ONES__);
    if (system_solution.err) {
        return system_solution;
    }
    // Solve Ux = y
    for (int i = 0; i < size; i++) {
        lu_matrix.content[i][size] = system_solution.solution[i];
    }
    system_solution = solve_upper_triangular_matrix(lu_matrix, __MATRIX_OPS_NONE_);
    if (system_solution.err) {
        return system_solution;
    }

    return system_solution;
}


/* Solve a square matrix by Doolittle method */
SystemSolution doolittle_method_solver(AugmentedMatrix matrix) {
    int size = matrix.rows;
    double **mtxc = matrix.content;

    SystemSolution system_solution = matrix_lu_decomposition(mtxc, size);
    if (system_solution.err) {
        system_solution.err |= __MATRIX_ERR_NO_SOLUTION__;
        return system_solution;
    }
    double determinant = system_solution.determinant;
    solution_free(system_solution);

    system_solution = doolittle_method_solve_lu(matrix);
    if (system_solution.err) {
        system_solution.err |= __MATRIX_ERR_NO_SOLUTION__;
        return system_solution;
    }

    system_solution.determinant = determinant;
    return system_solution;
}

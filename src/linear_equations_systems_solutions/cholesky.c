/**
    ANSI C standard: c11
    {file}.c
    Purpose: {Description}

   @author Esaú Peralta
   @email esau.opr@gmail.com
*/

#include <stdlib.h>
#include "../matrix/matrix_ldlt.h"
#include "../linear_equations_systems_solutions/backward_substitution.h"

#define CHOLESKY_IMPORT
#include "cholesky.h"


SystemSolution solve_by_cholesky_method(AugmentedMatrix matrix) {
    int size = matrix.rows;
    double **mtxc = matrix.content;

    SystemSolution system_solution = matrix_ldlt_decomposition(mtxc, size);
    if (system_solution.err & __MATRIX_ERR_NO_LDLT_DECOMPOSITION__) {
        system_solution.err |= __MATRIX_ERR_NO_SOLUTION__;
        return system_solution;
    }
    double determinat = system_solution.determinant;

    // Multiply L x D in the same matrix, this LD is matriz is a lower traingular matrix
    for (int i = 1; i < size; i++) {
        for (int j = 0; j < i; j++){
            mtxc[i][j] *= mtxc[j][j];
        }
    }
    // Solve Ly = b where L has a diagonal with ones
    system_solution = solve_lower_triangular_matrix(matrix, __MATRIX_OPS_NONE_);
    // Solve Ux = y
    for (int i = 0; i < size; i++) {
        mtxc[i][size] = system_solution.solution[i];
    }
    solution_free(system_solution);
    system_solution = solve_upper_triangular_matrix(matrix, __MATRIX_OPS_DIAG_HAS_ONES__);

    system_solution.determinant = determinat;
    return system_solution;
}

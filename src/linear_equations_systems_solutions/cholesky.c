/**
    ANSI C standard: c11
    {file}.c
    Purpose: {Description}

   @author Esaú Peralta
   @email esau.opr@gmail.com
*/

#include <stdlib.h>
#include "../matrix/matrixLDLt.h"
#include "../linear_equations_systems_solutions/backward_substitution.h"

#define CHOLESKY_IMPORT
#include "cholesky.h"


SystemSolution solve_by_cholesky_method(AugmentedMatrix matrix) {
    int size = matrix.rows;
    double **mtxc = matrix.content;

    SystemSolution system_solution = LDLt_decomposition(mtxc, size);
    if (system_solution.size == -1) {
        return system_solution;
    }

    // Multiply L x D in the same matrix, this LD is matriz is a lower traingular matrix
    for (int i = 1; i < size; i++) {
        for (int j = 0; j < i; j++){
            mtxc[i][j] *= mtxc[j][j];
        }
    }




    // Solve Ly = b where L has a diagonal with ones
    system_solution.solution = solve_lower_triangular_matrix(matrix, __NO_MATRIX_FLAGS__).solution;

    // Solve Ux = y
    for (int i = 0; i < size; i++) {
        mtxc[i][size] = system_solution.solution[i];
    }
    free(system_solution.solution);
    system_solution.solution = solve_upper_triangular_matrix(matrix, __DIAGONAL_HAS_ONES__).solution;

    return system_solution;
}

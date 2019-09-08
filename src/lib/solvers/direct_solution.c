/**
    ANSI C standard: c11
    direct_solution.c
    Purpose: Implementation for a direct solution when the matrix is
    a diagonal matrix

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#define DIRECT_SOLUTION_IMPORT
#include "numsys/solvers/direct_solution.h"

/* solver for a diagonal matrix */
void solver_diagonal_matrix(NSMatrixSystem * msystem) {
    double ** matrix = msystem->a.items;
    int size = msystem->a.rows;

    msystem->a.determinant = 1.0;

    for (int i = 0; i < size; i++) {
        msystem->x.items[i] = matrix[i][size] / matrix[i][i];
        msystem->a.determinant *= matrix[i][i];
    }
}

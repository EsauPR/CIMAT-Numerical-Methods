/**
    ANSI C standard: c11
    backward_substitutions.c
    Purpose: Implementation for backward substitution algorithms

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#define BWFW_SUBSTITUTION_IMPORT
#include "numsys/solvers/bwfw_substitution.h"


/*
    Return array with the solution for a lower triangular matrix
    using backward substitution

    Use the flag 'NS__MATRIX_OPS_DIAG_HAS_ONES__' to asume that the diagonal is fullfiled with ones
*/
void solver_forward_substitution(NSMatrixSystem * msystem, NS__flag_ops flags) {
    double **matrix = msystem->a.items;
    double tmp;
    int size = msystem->a.rows;
    msystem->a.determinant = 1.0;

    for (int i = 0; i < size; i++) {
        if (NS_IS_ZERO(matrix[i][i])) {
            msystem->err |= NS__MATRIX_ERR_HAS_ZERO_ON_DIAG__;
            return;
        }

        tmp = matrix[i][size];
        for (int j = 0; j < i; j++) {
            tmp -= matrix[i][j] * msystem->x.items[j];
        }

        if (!(flags & NS__MATRIX_OPS_DIAG_HAS_ONES__)) {
            tmp /= matrix[i][i];
        }

        msystem->x.items[i] = tmp;
        msystem->a.determinant *= matrix[i][i];
    }
}

/*
    Return array with the solution for a upper triangular matrix
    using backward substitution

    Use the flag 'NS__MATRIX_OPS_DIAG_HAS_ONES__' to asume that the diagonal is fullfiled with ones
*/
void solver_backward_substitution(NSMatrixSystem * msystem, NS__flag_ops flags) {
    double **matrix = msystem->a.items;
    double tmp;
    int size = msystem->a.rows;
    msystem->a.determinant = 1.0;

    for (int i = size - 1; i >= 0; i--) {
        if (NS_IS_ZERO(matrix[i][i])) {
            msystem->err |= NS__MATRIX_ERR_HAS_ZERO_ON_DIAG__;
            return;
        }
        tmp = matrix[i][size];
        for (int j = i + 1; j < size; j++) {
            tmp -= matrix[i][j] * msystem->x.items[j];
        }
        if (!(flags & NS__MATRIX_OPS_DIAG_HAS_ONES__)) {
            tmp /= matrix[i][i];
        }
        msystem->x.items[i] = tmp;
        msystem->a.determinant *= matrix[i][i];
    }
}

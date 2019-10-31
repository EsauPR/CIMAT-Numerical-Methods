/**
    ANSI C standard: c11
    gaussian_elimination.c
    Purpose: Implementation guassian elimination algorithm

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include "numsys/solvers/bwfw_substitution.h"

#define GAUSSIAN_ELIMINATION_IMPORT
#include "numsys/solvers/gaussian_elimination.h"


/* Create the row pivot */
static void gaussian_elimination_make_row_pivot(double **a, double * b, int size, int pivot) {
    b[pivot] /= a[pivot][pivot];
    for (int k = size - 1; k >= pivot; k--) {
        a[pivot][k] /=  a[pivot][pivot];
    }
}


/* Make zeros all the elements under of the col pivot */
static void gaussian_elimination_make_cols_zeros(double ** a, double * b, int size, int pivot) {
    for (int i = pivot + 1; i < size; i++) {
        b[i] -= a[i][pivot] * b[pivot];
        for (int k = size - 1; k >= pivot; k--) {
            a[i][k] -= a[pivot][k] * a[i][pivot];
        }
    }
}


/* Solve a square matrix by gaussian elimination without pivot */
void solver_gaussian_elimination_simple(NSMatrixSystem * msystem) {
    double **matrix = msystem->a.items;
    double * b = msystem->b.items;
    int size = msystem->a.rows;

    msystem->a.determinant = 1.0;

    for (int pivot = 0; pivot < size; pivot++) {
        // Replaze the pivots with value zero
        if (matrix[pivot][pivot] == 0) {
            NSMatrixElem mp = matrix_find_max_element(matrix, pivot + 1, size, pivot, pivot + 1, NS__MATRIX_OPS_NONE_);

            if (NS_IS_ZERO(mp.value)) {
                msystem->err |= NS__MATRIX_ERR_NO_SOLUTION__;
                return;
            }

            matrix_swap_rows(msystem->a, pivot, mp.row);
            NS_SWAP(msystem->b.items[pivot], msystem->b.items[mp.row], double);
            msystem->a.determinant *= -1.0;
        }

        msystem->a.determinant *= matrix[pivot][pivot];
        gaussian_elimination_make_row_pivot(matrix, b, size, pivot);
        gaussian_elimination_make_cols_zeros(matrix, b, size, pivot);
    }

    solver_backward_substitution(msystem, NS__MATRIX_OPS_NONE_);
}


/* Return a array to track the solution positions when there are cols swaps */
static void gaussian_elimination_set_positions_map(int *positions_map, int size) {
    for (int i = 0; i < size; i++) {
        positions_map[i] = i;
    }
}


/* Sort the result by positions map */
static void gaussian_elimination_sort_result(double *result, int *positions_map, int size) {
    for (int i = 0; i < size; i++) {
        if (positions_map[i] == i) continue;

        int pos = positions_map[i];
        while(1) {
            pos = positions_map[pos];
            if (positions_map[pos] == i) break;
        }

        NS_SWAP(result[i], result[pos], double);
        NS_SWAP(positions_map[i], positions_map[pos], double);
    }
}


/* Solve a square matrix by gaussian elimination with pivot */
void solver_gaussian_elimination(NSMatrixSystem * msystem) {
    double **matrix = msystem->a.items;
    double * b = msystem->b.items;
    int size = msystem->a.rows;

    int * positions_map = matrixio_allocate_array_int(size);
    gaussian_elimination_set_positions_map(positions_map, size);
    msystem->cols_perm_map = positions_map;

    msystem->a.determinant = 1.0;

    for (int pivot = 0; pivot < size; pivot++) {
        printf("pivot: %d\n", pivot);
        NSMatrixElem mp = matrix_find_max_element(matrix, pivot, size, pivot, size, NS__MATRIX_OPS_NONE_);

        if (NS_IS_ZERO(mp.value)) {
            msystem->err |= NS__MATRIX_ERR_NO_SOLUTION__;
            return;
        }

        // Swap rows and columns
        if (NS_ABS(matrix[pivot][pivot]) != NS_ABS(mp.value)) {
            if ( pivot != mp.row) {
                matrix_swap_rows(msystem->a, pivot, mp.row);
                NS_SWAP(msystem->b.items[pivot], msystem->b.items[mp.row], double);
                msystem->a.determinant *= -1.0;
            }

            if ( pivot != mp.col) {
                matrix_swap_cols(msystem->a, pivot, mp.col);
                NS_SWAP(positions_map[pivot], positions_map[mp.col], int);
                msystem->a.determinant *= -1.0;
            }
        }

        msystem->a.determinant *= matrix[pivot][pivot];
        gaussian_elimination_make_row_pivot(matrix, b, size, pivot);
        gaussian_elimination_make_cols_zeros(matrix, b, size, pivot);
    }

    solver_backward_substitution(msystem, NS__MATRIX_OPS_NONE_);
    gaussian_elimination_sort_result(msystem->x.items, positions_map, size);
}

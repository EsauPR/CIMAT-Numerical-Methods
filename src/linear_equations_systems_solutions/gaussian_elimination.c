/**
    ANSI C standard: c11
    gaussian_elimination.c
    Purpose: Implementation guassian elimination algorithm

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include "backward_substitution.h"

#define GAUSSIAN_ELIMINATION_IMPORT
#include "gaussian_elimination.h"


/* Create the row pivot */
static void gaussian_elimination_make_row_pivot(double **matrix, int size, int pivot) {
    for (int k = size; k >= pivot; k--) {
        matrix[pivot][k] /=  matrix[pivot][pivot];
    }
}


/* Make zeros all the elements under of the col pivot */
static void gaussian_elimination_make_cols_zeros(double **matrix, int size, int pivot) {
    for (int i = pivot + 1; i < size; i++) {
        for (int k = size; k >= pivot; k--) {
            matrix[i][k] =  matrix[i][k] - matrix[pivot][k] * matrix[i][pivot];
        }
    }
}


/* Solve a square matrix by gaussian elimination without pivot */
SystemSolution solve_by_simple_gaussian_elimination(AugmentedMatrix matrix) {
    double **mtxa = matrix.content;
    int size = matrix.rows;

    SystemSolution system_solution = SystemSolutionDefault;
    system_solution.solution = NULL;
    system_solution.size = size;
    system_solution.determinant = 1.0;

    for (int pivot = 0; pivot < size; pivot++) {
        // Replaze the pivots with value zero
        if (mtxa[pivot][pivot] == 0) {
            MatrixElement mp = matrix_find_max_element(mtxa, pivot + 1, size, pivot, pivot + 1);

            if (mp.value == 0.0) {
                return system_solution; // There is not solution
            }

            matrix_swap_rows(mtxa, pivot, mp.row);
            system_solution.determinant *= -1.0;
        }

        system_solution.determinant *= mtxa[pivot][pivot];
        gaussian_elimination_make_row_pivot(mtxa, size, pivot);
        gaussian_elimination_make_cols_zeros(mtxa, size, pivot);
    }

    system_solution.solution = solve_upper_triangular_matrix(matrix, __MATRIX_NO_FLAGS__).solution;
    return system_solution;
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

        SWAP(result[i], result[pos]);
        SWAP(positions_map[i], positions_map[pos]);
    }
}


/* Solve a square matrix by gaussian elimination with pivot */
SystemSolution solve_by_gaussian_elimination(AugmentedMatrix matrix) {
    double **mtxa = matrix.content;
    int size = matrix.rows;

    int positions_map[size];
    gaussian_elimination_set_positions_map(positions_map, size);

    SystemSolution system_solution = SystemSolutionDefault;
    system_solution.solution = NULL;
    system_solution.size = size;
    system_solution.determinant = 1.0;

    for (int pivot = 0; pivot < size; pivot++) {
        MatrixElement mp = matrix_find_max_element(mtxa, pivot, size, pivot, size);

        if (mp.value == 0.0) {
            return system_solution;
        }

        // Swap rows and columns
        if (ABS(mtxa[pivot][pivot]) != ABS(mp.value)) {
            if ( pivot != mp.row) {
                matrix_swap_rows(mtxa, pivot, mp.row);
                system_solution.determinant *= -1.0;
            }

            if ( pivot != mp.col) {
                matrix_swap_cols(mtxa, size, pivot, mp.col);
                SWAP(positions_map[pivot], positions_map[mp.col]);
                system_solution.determinant *= -1.0;
            }
        }

        system_solution.determinant *= mtxa[pivot][pivot];
        gaussian_elimination_make_row_pivot(mtxa, size, pivot);
        gaussian_elimination_make_cols_zeros(mtxa, size, pivot);
    }

    system_solution.solution = solve_upper_triangular_matrix(matrix, __MATRIX_NO_FLAGS__).solution;
    gaussian_elimination_sort_result(system_solution.solution, positions_map, size);

    return system_solution;
}

/**
    ANSI C standard: c11
    gaussian_elimination.c
    Purpose: Implementation guassian elimination algorithm

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>

#include "../matrix.h"
#include "backward_substitution.h"
#include "solution.h"

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
SystemSolution solve_by_simple_gaussian_elimination(double **matrix, int size) {
    SystemSolution system_solution;
    system_solution.solution = NULL;
    system_solution.size = size;
    system_solution.determinat = 1.0;

    for (int pivot = 0; pivot < size; pivot++) {
        // Replaze the pivots with value zero
        if (matrix[pivot][pivot] == 0) {
            MatrixElement mp = find_matrix_max_element(matrix, pivot + 1, pivot, size - 1, pivot);

            if (mp.value == 0.0) {
                return system_solution; // There is not solution
            }

            swap_matrix_rows(matrix, size + 1, pivot, mp.row);
        }

        gaussian_elimination_make_row_pivot(matrix, size, pivot);
        gaussian_elimination_make_cols_zeros(matrix, size, pivot);
    }

    system_solution.solution = solve_upper_triangular_matrix(matrix, size).solution;
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
        if (positions_map[i] != i) {
            SWAP(result[i], result[positions_map[i]]);
            positions_map[positions_map[i]] = positions_map[i];
            positions_map[i] = i;
        }
    }
}


/* Solve a square matrix by gaussian elimination with pivot */
SystemSolution solve_by_gaussian_elimination(double **matrix, int size) {
    int positions_map[size];
    gaussian_elimination_set_positions_map(positions_map, size);

    SystemSolution system_solution;
    system_solution.solution = NULL;
    system_solution.size = size;
    system_solution.determinat = 1.0;

    for (int pivot = 0; pivot < size; pivot++) {
        MatrixElement mp = find_matrix_max_element(matrix, pivot, pivot, size - 1, size - 1);

        if (mp.value == 0.0) {
            return system_solution;
        }

        // Swap rows and columns
        if (ABS(matrix[pivot][pivot]) != ABS(mp.value)) {
            if ( pivot != mp.row) {
                swap_matrix_rows(matrix, size + 1, pivot, mp.row);
            }

            if ( pivot != mp.col) {
                swap_matrix_cols(matrix, size, pivot, mp.col);
                SWAP(positions_map[pivot], positions_map[mp.col]);
            }
        }

        gaussian_elimination_make_row_pivot(matrix, size, pivot);
        gaussian_elimination_make_cols_zeros(matrix, size, pivot);
    }

    system_solution.solution = solve_upper_triangular_matrix(matrix, size).solution;
    gaussian_elimination_sort_result(system_solution.solution, positions_map, size);

    return system_solution;
}

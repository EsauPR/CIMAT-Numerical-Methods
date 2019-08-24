/**
    ANSI C standard: c11
    solution.c
    Purpose: Implementation for a system solution module

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#include <stdio.h>
#include "../matrix/matrixio.h"

#define SOLUTION_IMPORT
#include "solution.h"


/* Return a pointer array to track a permutation mapping */
int *create_permutation_map(int size) {
    int *map = allocate_array(size, __T_INT);

    for (int i = 0; i < size; i++) {
        map[i] = i;
    }

    return map;
}

/* Free the solution struct for a linear equation system*/
void free_system_solution(SystemSolution * system_solution) {
    if (system_solution->solution != NULL) {
        free(system_solution->solution);
        system_solution->solution = NULL;
    }
    if (system_solution->rows_perm_map != NULL) {
        free(system_solution->rows_perm_map);
        system_solution->rows_perm_map = NULL;
    }
    if (system_solution->cols_perm_map != NULL) {
        free(system_solution->cols_perm_map);
        system_solution->cols_perm_map = NULL;
    }
}

/* Print the solution for a linear equation system*/
void print_system_solution(SystemSolution system_solution) {
    for (int i = 0; i < system_solution.size; i++){
        printf("X_%d = %lf\n", i + 1, system_solution.solution[i]);
    }
    puts("");

    printf("Determinant: %lf\n", system_solution.determinant);
}

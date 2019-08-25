/**
    ANSI C standard: c11
    solution.c
    Purpose: Implementation for a system solution module

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#include <stdio.h>
#include <stdlib.h>
#include "../matrix/matrixio.h"

#define SOLUTION_IMPORT
#include "solution.h"


/* Return a pointer array to track a permutation mapping */
int *solution_create_permutation_map(int size) {
    int * map = matrixio_allocate_int_array(size);
    for (int i = 0; i < size; map[i] = i, i++);
    return map;
}

/*
    Free the solution struct for a linear equation system
    Returns the same struct values with NULL on freeded pointers
*/
SystemSolution solution_free(SystemSolution system_solution) {
    if (system_solution.solution != NULL) {
        free(system_solution.solution);
        system_solution.solution = NULL;
    }
    if (system_solution.rows_perm_map != NULL) {
        free(system_solution.rows_perm_map);
        system_solution.rows_perm_map = NULL;
    }
    if (system_solution.cols_perm_map != NULL) {
        free(system_solution.cols_perm_map);
        system_solution.cols_perm_map = NULL;
    }

    return system_solution;
}

/* Print the solution for a linear equation system*/
void solution_show(SystemSolution system_solution) {
    for (int i = 0; i < system_solution.size; i++){
        printf("X_%d = %lf\n", i + 1, system_solution.solution[i]);
    }
    puts("");

    printf("Determinant: %lf\n", system_solution.determinant);
}

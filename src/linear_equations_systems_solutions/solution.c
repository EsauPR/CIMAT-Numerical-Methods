/**
    ANSI C standard: c11
    solution.c
    Purpose: Implementation for a system solution module

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#include <stdio.h>

#define SOLUTION_IMPORT
#include "solution.h"

/* Print the solution for a linear equation system*/
void print_system_solution(SystemSolution system_solution) {
    for (int i = 0; i < system_solution.size; i++){
        printf("X_%d = %lf\n", i + 1, system_solution.solution[i]);
    }
    puts("");

    printf("Determinant: %lf\n", system_solution.determinant);
}

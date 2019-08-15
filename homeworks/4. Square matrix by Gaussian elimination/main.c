/**
    ANSI C standard: c11
    Purpose: Solve a square matrix by Gaussian elimination

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include "../../src/matrix.h"
#include "../../src/linear_equations_systems_solutions/gaussian_elimination.h"


int main(int argc, char const *argv[]) {
    int size;

    scanf("%d", &size);

    double **matrix = read_augmented_square_matrix(size);
    print_matrix(matrix, size, size + 1);

    SystemSolution system_solution = solve_by_simple_gaussian_elimination(matrix, size);

    if (system_solution.solution == NULL) {
        puts("The sysyem has not a unique solution");
        return 0;
    }

    print_system_solution(system_solution);

    free_squared_augmented_matriz(matrix, size);
    free(system_solution.solution);

    return 0;
}

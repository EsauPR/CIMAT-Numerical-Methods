/**
    ANSI C standard: c11
    Purpose: Solve a lower triangular matrix

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include "../../src/matrix.h"
#include "../../src/linear_equations_systems_solutions/backward_substitution.h"


int main(int argc, char const *argv[]) {
    int size;

    scanf("%d", &size);

    double **matrix = read_augmented_square_matrix(size);
    print_matrix(matrix, size, size + 1);

    SystemSolution system_solution = solve_lower_triangular_matrix(matrix, size);
    print_system_solution(system_solution);

    free_squared_augmented_matriz(matrix, size);
    free(system_solution.solution);

    return 0;
}

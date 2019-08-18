/**
    ANSI C standard: c11
    Purpose: Solve a lower triangular matrix

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include "../../src/matrix/matrixio.h"
#include "../../src/linear_equations_systems_solutions/backward_substitution.h"


int main() {
    int size;

    scanf("%d", &size);

    double **matrix = read_matrix(size, size + 1);
    print_matrix(matrix, size, size + 1);

    SystemSolution system_solution = solve_lower_triangular_matrix(matrix, size);
    print_system_solution(system_solution);

    free_matriz(matrix, size);
    free(system_solution.solution);

    return 0;
}

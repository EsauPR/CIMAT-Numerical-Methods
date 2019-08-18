/**
    ANSI C standard: c11
    Purpose: Solve a square matrix by Gaussian elimination

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>

#include "../../src/matrix/matrixio.h"
#include "../../src/linear_equations_systems_solutions/solution.h"
#include "../../src/linear_equations_systems_solutions/doolittle.h"


int main() {
    int size;

    scanf("%d", &size);

    double **matrix = read_matrix(size, size + 1);
    print_matrix(matrix, size, size + 1);

    SystemSolution system_solution = solve_by_doolittle_method(matrix, size);
    print_matrix(matrix, size, size + 1);

    if ( system_solution.solution == NULL) {
        puts("The system has not a unique solution");
        return 0;
    }

    print_system_solution(system_solution);

    free_matriz(matrix, size);
    free(system_solution.solution);

    return 0;
}

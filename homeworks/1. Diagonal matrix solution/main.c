/**
    ANSI C standard: c11
    Purpose: Solve a diagonal matrix

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "../../src/matrix/matrixio.h"
#include "../../src/linear_equations_systems_solutions/direct_solution.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        perror("main(): 2 Args missing");
        exit(EXIT_FAILURE);
    }

    AugmentedMatrix matrix = read_augmented_matrix(argv[1], argv[2]);
    print_matrix(matrix.content, matrix.rows, matrix.cols);

    SystemSolution system_solution = solve_diagonal_matrix(matrix);
    print_system_solution(system_solution);

    free_matriz(matrix);
    free_system_solution(system_solution);

    return 0;
}

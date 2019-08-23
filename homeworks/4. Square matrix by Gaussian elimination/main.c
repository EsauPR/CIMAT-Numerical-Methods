/**
    ANSI C standard: c11
    Purpose: Solve a square matrix by Gaussian elimination

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdlib.h>
#include "../../src/linear_equations_systems_solutions/gaussian_elimination.h"


int main(int argc, char *argv[]) {
    if (argc < 3) {
        perror("main(): 2 Args missing");
        exit(EXIT_FAILURE);
    }

    AugmentedMatrix matrix = read_augmented_matrix(argv[1], argv[2]);
    print_matrix(matrix.content, matrix.rows, matrix.cols);

    SystemSolution system_solution = solve_by_simple_gaussian_elimination(matrix);

    if (system_solution.solution == NULL) {
        puts("The system has not a unique solution");
        return 0;
    }

    print_system_solution(system_solution);

    free_matriz(matrix);
    free(system_solution.solution);

    return 0;
}

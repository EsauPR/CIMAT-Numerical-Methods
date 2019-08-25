/**
    ANSI C standard: c11
    Purpose: Solve a square matrix by Gaussian elimination

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#include <stdlib.h>
#include "../../src/linear_equations_systems_solutions/doolittle.h"


int main(int argc, char *argv[]) {
    if (argc < 3) {
        perror("main(): 2 Args missing");
        exit(EXIT_FAILURE);
    }

    AugmentedMatrix matrix = matrixio_read_augmented_matrix(argv[1], argv[2]);
    matrixio_show(matrix.content, matrix.rows, matrix.cols);

    SystemSolution system_solution = solve_by_doolittle_method(matrix);

    if ( system_solution.state & __SOLUTION_NO_EXISTS__) {
        puts("The system has not a unique solution");
    } else {
        solution_show(system_solution);
    }

    matrixio_free(matrix);
    solution_free(system_solution);

    return 0;
}

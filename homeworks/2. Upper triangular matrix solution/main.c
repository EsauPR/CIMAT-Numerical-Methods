/**
    ANSI C standard: c11
    Purpose: Solve a upper triangular matrix

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#include <stdlib.h>
#include "../../src/linear_equations_systems_solutions/backward_substitution.h"


int main(int argc, char *argv[]) {
    if (argc < 3) {
        perror("main(): 2 Args missing");
        exit(EXIT_FAILURE);
    }

    AugmentedMatrix matrix = matrixio_read_augmented_matrix(argv[1], argv[2]);
    matrixio_show(matrix.content, matrix.rows, matrix.cols);

    SystemSolution system_solution = solve_upper_triangular_matrix(matrix, __MATRIX_NO_FLAGS__);
    solution_show(system_solution);

    matrixio_free(matrix);
    solution_free(system_solution);

    return 0;
}

/**
    ANSI C standard: c11
    Purpose: Solve a lower triangular matrix

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdlib.h>
#include "../../src/linear_equations_systems_solutions/backward_substitution.h"


int main(int argc, char *argv[]) {
    if (argc < 3) {
        perror("main():: 2 Args missing");
        exit(EXIT_FAILURE);
    }

    AugmentedMatrix matrix = matrixio_read_augmented(argv[1], argv[2]);
    matrixio_show(matrix.content, matrix.rows, matrix.cols + matrix.cols_extra);

    __flag_err flags = matrix_check_dimensions(matrix) | matrix_verify_lower_triangular(matrix);
    if (flags) {
        pmerror("main():", flags);
        matrixio_free(matrix);
        exit(EXIT_FAILURE);
    }

    SystemSolution system_solution = solve_lower_triangular_matrix(matrix, __MATRIX_OPS_NONE_);
    solution_show(system_solution);

    matrixio_free(matrix);
    solution_free(system_solution);

    return EXIT_SUCCESS;
}

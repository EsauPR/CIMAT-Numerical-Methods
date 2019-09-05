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
        perror("main():: 2 Args missing");
        exit(EXIT_FAILURE);
    }

    AugmentedMatrix matrix = matrixio_read_augmented(argv[1], argv[2]);
    matrixio_show(matrix.content, matrix.rows, matrix.cols + matrix.cols_extra);

    __flag_err flags = matrix_check_dimensions(matrix);
    if (flags) {
        pmerror("main():", flags);
        matrixio_free(matrix);
        exit(EXIT_FAILURE);
    }

    SystemSolution system_solution = doolittle_method_solver(matrix);

    if (system_solution.err) {
        pmerror("main():", system_solution.err);
        matrixio_free(matrix);
        solution_free(system_solution);
        exit(EXIT_FAILURE);
    }

    solution_show(system_solution);

    matrixio_free(matrix);
    solution_free(system_solution);

    return 0;
}

/**
    ANSI C standard: c11
    Purpose: Solve a square matrix by Gauss Seidel method

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#include <stdlib.h>
#include "../../src/linear_equations_systems_solutions/gauss_seidel.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        perror("main():: 2 Args missing");
        exit(EXIT_FAILURE);
    }

    Matrix matrix = matrixio_fread_matrix_system(argv[1], argv[2]);
    matrixio_show_matrix(matrix.items, matrix.rows, matrix.cols + matrix.cols_extra);

    NS__flag_err flags = matrix_check_dimensions(matrix);
    if (flags) {
        nsperror("main():", flags);
        matrixio_free_matrix_system(&msystem);
        exit(EXIT_FAILURE);
    }

    SystemSolution ss = gauss_seidel_solver(matrix);

    if (ss.err) {
        nsperror("main():", ss.err);
        matrixio_free_matrix(matrix);
        solution_free(ss);
        exit(EXIT_FAILURE);
    }

    solution_show(ss);

    matrixio_free_matrix(matrix);
    solution_free(ss);

    return 0;
}

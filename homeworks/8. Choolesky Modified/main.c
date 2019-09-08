/**
    ANSI C standard: c11
    Purpose: Solve a square matrix by Gaussian elimination

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#include <stdlib.h>
#include "numsys/matrix/matrix.h"
#include "numsys/solvers/cholesky.h"


int main(int argc, char *argv[]) {
    if (argc < 3) {
        perror("main():: 2 Args missing");
        exit(EXIT_FAILURE);
    }

    AugmentedMatrix matrix = matrixio_fread_matrix_system(argv[1], argv[2]);
    matrixio_show_matrix(matrix.items, matrix.rows, matrix.cols + matrix.cols_extra);

    NS__flag_err flags = matrix_check_dimensions(matrix) | matrix_verify_symmetry(matrix);
    if (flags) {
        nsperror("main():", flags);
        matrixio_free_matrix_system(&msystem);
        exit(EXIT_FAILURE);
    }

    SystemSolution system_solution = solver_cholesky_method(matrix);

    if (system_solution.err) {
        nsperror("main():", system_solution.err);
        matrixio_free_matrix(matrix);
        solution_free(system_solution);
        exit(EXIT_FAILURE);
    }

    solution_show(system_solution);

    matrixio_free_matrix_system(&msystem);

    return 0;
}

/**
    ANSI C standard: c11
    Purpose: Solve a matrix system Ax=b by Jacobi method

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#include <stdlib.h>
#include <numsys/matrix/matrix.h>
#include "numsys/solvers/jacobi.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        perror("main():: 2 Args missing");
        exit(EXIT_FAILURE);
    }

    NSMatrixSystem msystem = matrixio_fread_matrix_system(argv[1], argv[2]);
    matrixio_show_matrix_system(msystem, !NS__MATRIXIO_SHOW_SOL);

    NS__flag_err flags = matrix_check_dimensions(msystem.a);
    if (flags) {
        nsperror("main():", flags);
        matrixio_free_matrix_system(&msystem);
        exit(EXIT_FAILURE);
    }

    jacobi_solver(&msystem);

    if (msystem.err) {
        nsperror("main():", msystem.err);
        matrixio_free_matrix_system(&msystem);
        exit(EXIT_FAILURE);
    }

    matrixio_show_matrix_system(msystem, NS__MATRIXIO_SHOW_SOL);
    matrixio_free_matrix_system(&msystem);

    return 0;
}

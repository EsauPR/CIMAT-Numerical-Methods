/**
    ANSI C standard: c11
    Purpose: Solve a square matrix by Gaussian elimination

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdlib.h>
#include "numsys/matrix/matrix.h"
#include "numsys/solvers/gaussian_elimination.h"


int main(int argc, char *argv[]) {
    NSMatrixSystem msystem = matrixio_fread_matrix_system(argv[1], argv[2]);
    matrixio_show_matrix_system(msystem, !NS__MATRIXIO_SHOW_SOL);

    NS__flag_err flags = matrix_check_dimensions(msystem.a);
    if (flags) {
        nsperror("main():", flags);
        matrixio_free_matrix_system(&msystem);
        exit(EXIT_FAILURE);
    }

    solver_gaussian_elimination(&msystem);
    if (msystem.err) {
        nsperror("main():", msystem.err);
        matrixio_free_matrix_system(&msystem);
        exit(EXIT_FAILURE);
    }

    matrixio_show_matrix_system(msystem, NS__MATRIXIO_SHOW_SOL);
    matrixio_free_matrix_system(&msystem);

    return 0;
}

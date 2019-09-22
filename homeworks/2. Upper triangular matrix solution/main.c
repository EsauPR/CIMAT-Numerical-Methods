/**
    ANSI C standard: c11
    Purpose: Solve a upper triangular matrix

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#include <stdlib.h>
#include "numsys/solvers/bwfw_substitution.h"


int main(int argc, char *argv[]) {
    if (argc < 3) {
        perror("main():: 2 Args missing");
        exit(EXIT_FAILURE);
    }

    NSMatrixSystem msystem = matrixio_fread_matrix_system(argv[1], argv[2]);
    matrixio_show_matrix_system(msystem, !NS__MATRIXIO_SHOW_SOL);

    NS__flag_err flags = matrix_check_dimensions(msystem.a) | matrix_verify_upper_triangular(msystem.a);
    if (flags) {
        nsperror("main():", flags);
        matrixio_free_matrix_system(&msystem);
        exit(EXIT_FAILURE);
    }

    solver_backward_substitution(&msystem, NS__MATRIX_OPS_NONE_);
    matrixio_show_matrix_system(msystem, NS__MATRIXIO_SHOW_SOL);

    matrixio_free_matrix_system(&msystem);

    return EXIT_SUCCESS;
}

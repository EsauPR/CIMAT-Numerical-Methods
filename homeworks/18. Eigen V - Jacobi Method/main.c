/**
    ANSI C standard: c11
    Purpose: Find the all the eigen values and eigen vectors
    by Jacobi Method

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#include <stdlib.h>
#include "numsys/matrix/matrix.h"
#include "numsys/matrix_op/eigen_v/jacobi.h"


int main(int argc, char *argv[]) {
    if (argc < 2) {
        perror("main():: 1 Args missing");
        exit(EXIT_FAILURE);
    }

    NSMatrix matrix = matrixio_fread_matrix(argv[1]);
    matrixio_show_matrix(matrix);

    NS__flag_err flags = matrix_check_dimensions(matrix);
    if (flags) {
        nsperror("main():", flags);
        matrixio_free_matrix(&matrix);
        exit(EXIT_FAILURE);
    }

    NSMatrix eigen_vectors = matrix_eigen_jacobi_method(& matrix);
    matrixio_show_matrix(matrix);
    matrixio_show_matrix(eigen_vectors);

    matrixio_free_matrix(&eigen_vectors);
    matrixio_free_matrix(&matrix);

    return 0;
}

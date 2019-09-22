/**
    ANSI C standard: c11
    Purpose: Obtain the eigen values for a matrix
    by QR MEthod

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#include <stdlib.h>
#include "numsys/matrix/matrix.h"
#include "numsys/matrix_op/matrix_qr.h"
#include "numsys/matrix_op/eigen_v/qr.h"


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

    NSMatrix I = matrix_eigen_qr_method(&matrix);

    puts("Eigen Values");
    matrixio_show_matrix(matrix);
    puts("Eigen Vectors");
    matrixio_show_matrix(I);

    matrixio_free_matrix(&I);
    matrixio_free_matrix(&matrix);

    return 0;
}

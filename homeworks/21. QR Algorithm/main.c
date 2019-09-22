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
    if (argc < 1) {
        perror("main():: 2 Args missing");
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

    // NSMatrix R = matrixio_allocate_matrix(matrix.rows, matrix.cols);
    // matrix_qr_decomposition(&matrix, &R);
    // puts("Q");
    // matrixio_show_matrix(matrix);
    // puts("R");
    // matrixio_show_matrix(R);
    // NSMatrix QR = matrix_multiply_mm(matrix, R);
    // puts("QR");
    // matrixio_show_matrix(QR);
    // matrixio_free_matrix(&QR);
    // matrixio_free_matrix(&R);


    NSMatrix Q = matrix_eigen_qr_method(&matrix);
    // puts("Eigen Vectors");
    // matrixio_show_matrix(Q);
    puts("Eigen Values");
    matrixio_show_matrix(matrix);
    matrixio_free_matrix(&Q);

    matrixio_free_matrix(&matrix);

    return 0;
}

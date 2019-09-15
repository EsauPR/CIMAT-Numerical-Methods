/**
    ANSI C standard: c11
    Purpose: Solve a square matrix by Gaussian elimination

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#include <stdlib.h>
#include "numsys/matrix/matrix.h"
#include "numsys/matrix_op/matrix_inverse.h"


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

    NSMatrix matrix_copy = matrixio_copy_matrix(matrix);
    NSMatrix inverse = matrix_inverse_get(&matrix_copy);

    if (inverse.err) {
        nsperror("main():", matrix.err);
        matrixio_free_matrix(&matrix);
        matrixio_free_matrix(&matrix_copy);
        matrixio_free_matrix(&inverse);
        exit(EXIT_FAILURE);
    }

    matrixio_show_matrix(inverse);

    NSMatrix identity = matrix_multiply_mm(matrix, inverse);
    matrixio_show_matrix(identity);

    matrixio_free_matrix(&matrix);
    matrixio_free_matrix(&matrix_copy);
    matrixio_free_matrix(&inverse);
    matrixio_free_matrix(&identity);

    return 0;
}

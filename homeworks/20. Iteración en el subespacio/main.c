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
#include "numsys/matrix_op/eigen_v/subspace_iteration.h"


int main(int argc, char *argv[]) {
    if (argc < 1) {
        perror("main():: 2 Args missing");
        exit(EXIT_FAILURE);
    }

    NSMatrix matrix = matrixio_fread_matrix(argv[1]);
    // matrixio_show_matrix(matrix);

    int neigen;
    printf("Quantity of eigen values to compute [1 to %d]: ", matrix.rows);
    scanf("%d", &neigen);

    NS__flag_err flags = matrix_check_dimensions(matrix);
    if (flags) {
        nsperror("main():", flags);
        matrixio_free_matrix(&matrix);
        exit(EXIT_FAILURE);
    }


    NSMatrix eigenv = matrix_eigen_subspace_iteration_method(&matrix, neigen);

    puts("Eigen Values");
    matrixio_show_matrix(matrix);
    puts("Eigen Vectors");
    matrixio_show_matrix(eigenv);

    matrixio_free_matrix(&eigenv);
    matrixio_free_matrix(&matrix);

    return 0;
}

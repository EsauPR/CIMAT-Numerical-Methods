/**
    ANSI C standard: c11
    Purpose: Find the max eigen value and eigen vector by the Pow method

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#include <stdlib.h>
#include "numsys/matrix/matrix.h"
#include "numsys/matrix_op/eigen_v/pow.h"


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

    NSEigenV ev = matrix_eigen_pow_method(& matrix);

    printf("Eigen Value: %.10lf\n", ev.eigen_value);
    puts("Eigen Vector:");
    for (int i = 0; i < matrix.rows; i++) {
        printf("%.10lf ", ev.eigen_vector[i]);
    }
    puts("");

    matrixio_free_matrix(&matrix);
    matrixio_free_eigen_v(&ev);

    return 0;
}

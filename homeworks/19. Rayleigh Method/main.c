/**
    ANSI C standard: c11
    Purpose: Improve the eigen vector and eigen value given
    with the Rayleigh Method

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#include <stdlib.h>
#include "numsys/matrix/matrix.h"
#include "numsys/matrix_op/eigen_v/rayleigh.h"


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

    NSVector eigen_vector = matrixio_fread_vector(argv[2]);
    NSEigenV eigenv;
    eigenv.eigen_vector = eigen_vector.items;
    eigenv.eigen_value = 0;

    puts("Aprox Eigen vector:");
    for (int i = 0; i < matrix.rows; i++) {
        printf("%lf ", eigenv.eigen_vector[i]);
    }
    puts("");

    matrix_eigen_rayleigh_method(&matrix, &eigenv);

    printf("\nEigen Value: %lf\n", eigenv.eigen_value);
    puts("Eigen vector:");
    for (int i = 0; i < matrix.rows; i++) {
        printf("%lf ", eigenv.eigen_vector[i]);
    }
    puts("");

    matrixio_free_matrix(&matrix);
    matrixio_free_eigen_v(&eigenv);

    return 0;
}

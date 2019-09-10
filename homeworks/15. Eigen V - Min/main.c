/**
    ANSI C standard: c11
    Purpose: Solve a square matrix by Gauss Seidel method

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#include <stdlib.h>
#include "numsys/matrix/matrix.h"
#include "numsys/matrix_op/matrix_eigen_v.h"


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

    Matrix_Eigen_V ev = matrix_eigen_pow_method_inverse(& matrix);

    printf("Eigen Value: %.10lf\n", ev.eigen_value);
    puts("Eigen Vector:");
    for (int i = 0; i < matrix.rows; i++) {
        printf("%.10lf ", ev.eigen_vector[i]);
    }
    puts("");

    matrixio_free_matrix(&matrix);
    matrix_eigen_free(&ev);

    return 0;
}

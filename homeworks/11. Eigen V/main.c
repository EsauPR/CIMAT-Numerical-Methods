/**
    ANSI C standard: c11
    Purpose: Solve a square matrix by Gauss Seidel method

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#include <stdlib.h>
#include "../../src/matrix/matrix.h"
#include "../../src/matrix/matrix_eigen_v.h"


int main(int argc, char *argv[]) {
    if (argc < 1) {
        perror("main():: 2 Args missing");
        exit(EXIT_FAILURE);
    }

    Matrix matrix = matrixio_read(argv[1]);
    // matrixio_show(matrix.content, matrix.rows, matrix.cols);

    __flag_err flags = matrix_check_dimensions(matrix);
    if (flags) {
        pmerror("main():", flags);
        matrixio_free(matrix);
        exit(EXIT_FAILURE);
    }

    Matrix_Eigen_V ev = matrix_potence_method(matrix);

    printf("Eigen Value: %lf\n", ev.eigen_value);
    puts("Eigen Vector:");
    for (int i = 0; i < matrix.rows; i++) {
        printf("%lf ", ev.eigen_vector[i]);
    }
    puts("");

    matrixio_free(matrix);
    free(ev.eigen_vector);

    return 0;
}

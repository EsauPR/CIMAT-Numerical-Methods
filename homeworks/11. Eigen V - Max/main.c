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

    Matrix matrix = matrixio_fread_matrix(argv[1]);
    matrixio_show_matrix(matrix.items, matrix.rows, matrix.cols);

    NS__flag_err flags = matrix_check_dimensions(matrix);
    if (flags) {
        nsperror("main():", flags);
        matrixio_free_matrix_system(&msystem);
        exit(EXIT_FAILURE);
    }

    Matrix_Eigen_V ev = matrix_potence_method(matrix);

    printf("Eigen Value: %lf\n", ev.eigen_value);
    puts("Eigen Vector:");
    for (int i = 0; i < matrix.rows; i++) {
        printf("%.20lf ", ev.eigen_vector[i]);
    }
    puts("");

    matrixio_free_matrix(matrix);
    free(ev.eigen_vector);

    return 0;
}

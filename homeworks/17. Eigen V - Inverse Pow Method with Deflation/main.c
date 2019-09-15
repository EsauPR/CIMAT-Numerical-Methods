/**
    ANSI C standard: c11
    Purpose: Solve a square matrix by Gauss Seidel method

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#include <stdlib.h>
#include "numsys/matrix/matrix.h"
#include "numsys/matrix_op/eigen_v/pow.h"


int main(int argc, char *argv[]) {
    if (argc < 1) {
        perror("main():: 2 Args missing");
        exit(EXIT_FAILURE);
    }

    NSMatrix matrix = matrixio_fread_matrix(argv[1]);
    // matrixio_show_matrix(matrix);

    NS__flag_err flags = matrix_check_dimensions(matrix);
    if (flags) {
        nsperror("main():", flags);
        matrixio_free_matrix(&matrix);
        exit(EXIT_FAILURE);
    }

    int neigen = matrix.rows;
    NSEigenV * evs = matrix_eigen_pow_method_inv_dfl(& matrix, neigen);

    for (int k = 0; k < neigen; k++)
    {
        printf("\n%d)\nEigen Value: %.10lf\n", k+1, evs[k].eigen_value);
        puts("Eigen Vector:");
        for (int i = 0; i < matrix.rows; i++) {
            printf("%.10lf ", evs[k].eigen_vector[i]);
        }
        puts("");
    }

    matrixio_free_matrix(&matrix);
    for (int k = 0; k < neigen; k++) {
        matrixio_free_eigen_v(&(evs[k]));
    }
    free(evs);

    return 0;
}

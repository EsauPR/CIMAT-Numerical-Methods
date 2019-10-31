/**
    ANSI C standard: c11
    Purpose: Find the n eigen values and eigen vectors
    by the Pow Method with deflation

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#include <stdlib.h>
#include "numsys/matrix/matrix.h"
#include "numsys/matrix_op/eigen_v/jacobi.h"

void save_eigens(NSEigenV * evs, int neigen, int rows, const char * file_name) {
    FILE *fp = fopen(file_name, "w");
    if(fp == NULL) {
        perror("Can't open file to write");
        return;
    }

    for (int k = 0; k < neigen; k++) {
        fprintf(fp, "\n%d)\nEigen Value: %le\n", k+1, evs[k].eigen_value);
        fprintf(fp, "Eigen Vector:");
        for (int i = 0; i < rows; i++) {
            fprintf(fp, "%le ", evs[k].eigen_vector[i]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        perror("main():: 1 Args missing");
        exit(EXIT_FAILURE);
    }

    // int neigen = 10;

    // 10 max
    NSMatrix matrix = matrixio_fread_matrix(argv[1]);

    NSMatrix eigen_vectors = matrix_eigen_jacobi_method(&matrix);
    matrixio_save_matrix(matrix, "eigen_values.mtx");
    matrixio_save_matrix(eigen_vectors, "eigen_vectors.mtx");

    // // 10 min
    // NSMatrix matrix = matrixio_fread_matrix(argv[1]);
    // NSEigenV * evs = matrix_eigen_pow_method_inv_dfl(&matrix, neigen);
    // save_eigens(evs, neigen, matrix.rows, "max_eigens.txt");
    // matrixio_free_matrix(&matrix);
    // for (int k = 0; k < neigen; k++) {
    //     matrixio_free_eigen_v(&(evs[k]));
    // }
    // free(evs);

    matrixio_free_matrix(&eigen_vectors);
    matrixio_free_matrix(&matrix);

    return 0;
}

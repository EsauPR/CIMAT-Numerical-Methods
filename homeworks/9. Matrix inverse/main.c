/**
    ANSI C standard: c11
    Purpose: Solve a square matrix by Gaussian elimination

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#include <stdlib.h>
#include "../../src/matrix/matrix.h"
#include "../../src/matrix/matrix_inverse.h"


Matrix read_matrix(char* file_name) {
    int rows, cols;

    FILE *fp = fopen(file_name, "r");
    if(fp == NULL) {
        perror("fopen()");
        exit(EXIT_FAILURE);
    }

    fscanf(fp, "%d %d", &rows, &cols);

    // Add a extra col to make compatible with solvers
    Matrix matrix = matrixio_allocate(rows, cols + 1);
    matrix.cols = cols;
    matrix.cols_extra = 1;

    matrixio_scan(fp, matrix.content, 0, rows, 0, cols);
    fclose(fp);

    return matrix;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        perror("main():: 1 Args missing");
        exit(EXIT_FAILURE);
    }

    Matrix matrix = read_matrix(argv[1]);

    Matrix matrix_copy = matrixio_copy(matrix);
    matrixio_show(matrix_copy.content, matrix_copy.rows, matrix_copy.cols);

    __flag_err flags = matrix_check_dimensions(matrix);
    if (flags) {
        pmerror("main():", flags);
        matrixio_free(matrix);
        matrixio_free(matrix_copy);
        exit(EXIT_FAILURE);
    }

    Matrix inverse = matrix_inverse_get(matrix_copy);

    if (matrix.err) {
        pmerror("main():", matrix.err);
        matrixio_free(matrix);
        matrixio_free(matrix_copy);
        matrixio_free(inverse);
        exit(EXIT_FAILURE);
    }

    Matrix identity = matrix_multiply(matrix, inverse);
    matrixio_show(identity.content, identity.rows, identity.cols);

    matrixio_free(matrix);
    matrixio_free(matrix_copy);
    matrixio_free(inverse);
    matrixio_free(identity);

    return 0;
}

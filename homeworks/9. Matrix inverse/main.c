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
    Matrix matrix = matrixio_allocate_matrix(rows, cols + 1);
    matrix.cols = cols;
    matrix.cols_extra = 1;

    matrixio_scan_matrix(fp, matrix.items, 0, rows, 0, cols);
    fclose(fp);

    return matrix;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        perror("main():: 1 Args missing");
        exit(EXIT_FAILURE);
    }

    Matrix matrix = read_matrix(argv[1]);
    matrixio_show_matrix(matrix.items, matrix.rows, matrix.cols);

    NS__flag_err flags = matrix_check_dimensions(matrix);
    if (flags) {
        nsperror("main():", flags);
        matrixio_free_matrix_system(&msystem);
        exit(EXIT_FAILURE);
    }

    Matrix matrix_copy = matrixio_copy(matrix);
    Matrix inverse = matrix_inverse_get(matrix_copy);

    if (matrix.err) {
        nsperror("main():", matrix.err);
        matrixio_free_matrix(matrix);
        matrixio_free_matrix(matrix_copy);
        matrixio_free_matrix(inverse);
        exit(EXIT_FAILURE);
    }

    matrixio_show_matrix(inverse.items, inverse.rows, inverse.cols);

    Matrix identity = matrix_multiply(matrix, inverse);
    matrixio_show_matrix(identity.items, identity.rows, identity.cols);

    matrixio_free_matrix(matrix);
    matrixio_free_matrix(matrix_copy);
    matrixio_free_matrix(inverse);
    matrixio_free_matrix(identity);

    return 0;
}

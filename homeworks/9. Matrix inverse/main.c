/**
    ANSI C standard: c11
    Purpose: Solve a square matrix by Gaussian elimination

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#include <stdlib.h>
#include "../../src/matrix/matrix.h"
#include "../../src/matrix/matrix_inverse.h"


int main(int argc, char *argv[]) {
    int rows, cols;

    if (argc < 2) {
        perror("main(): 1 Args missing");
        exit(EXIT_FAILURE);
    }

    FILE *fp = fopen(argv[1], "r");
    if(fp == NULL) {
        perror("fopen()"); puts(argv[1]);
        exit(EXIT_FAILURE);
    }

    fscanf(fp, "%d %d", &rows, &cols);

    Matrix matrix = matrixio_allocate(rows, cols + 1);
    matrixio_read(fp, matrix.content, 0, rows, 0, cols);
    fclose(fp);

    Matrix matrix_copy = matrixio_copy(matrix);
    matrixio_show(matrix_copy.content, matrix_copy.rows, matrix_copy.rows);


    Matrix inverse = matrix_inverse_get(matrix_copy);

    if (inverse.state & __MATRIX_NO_INVERSE__) {
        puts("The system has not a unique solution");
    } else {
        matrixio_show(inverse.content, inverse.rows, inverse.cols);
    }

    Matrix identity = matrix_multiply_square_matrices(matrix, inverse);
    matrixio_show(identity.content, identity.rows, identity.cols);

    matrixio_free(matrix);
    matrixio_free(matrix_copy);
    matrixio_free(inverse);
    matrixio_free(identity);

    return 0;
}

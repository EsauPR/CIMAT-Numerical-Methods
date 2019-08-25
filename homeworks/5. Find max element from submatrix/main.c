/**
    ANSI C standard: c11
    Purpose: Solve a square matrix by Gaussian elimination

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdlib.h>
#include "../../src/matrix/matrixio.h"
#include "../../src/matrix/matrix.h"


int main(int argc, char *argv[]) {
    int rows, cols;

    if (argc < 2) {
        perror("main(): 1 Args missing");
        exit(EXIT_FAILURE);
    }

    FILE *fp = fopen(argv[1], "r");
    if(fp == NULL) {
        perror("fopen()");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    fscanf(fp, "%d %d", &rows, &cols);

    Matrix matrix = matrixio_allocate(rows, cols);
    matrixio_read(fp, matrix.content, 0, rows, 0, cols);
    fclose(fp);

    matrixio_show(matrix.content, rows, cols);

    MatrixElement mp = matrix_find_max_element(matrix.content, 0, rows, 0, cols);
    printf("El elemento con mayor valor obsoluto es: %lf, en (%d, %d)\n", mp.value, mp.row + 1, mp.col + 1);

    matrixio_free(matrix);

    return 0;
}

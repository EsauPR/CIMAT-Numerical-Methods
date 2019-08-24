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
        perror("fopen()");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    fscanf(fp, "%d %d", &rows, &cols);

    Matrix matrix = allocate_matrix(rows, cols + 1);
    read_matrix(fp, matrix.content, 0, rows, 0, cols);
    fclose(fp);

    Matrix inverse = get_matrix_inverse(matrix);

    if (inverse.state & __MATRIX_NO_INVERSE__) {
        puts("The system has not a unique solution");
    } else {
        print_matrix(inverse.content, inverse.rows, inverse.cols);
    }

    free_matriz(matrix);
    free_matriz(inverse);

    return 0;
}

/**
    ANSI C standard: c11
    Purpose: Solve a square matrix by Gauss Seidel method

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#include <stdlib.h>
#include "../../src/matrix/matrix.h"
#include "../../src/matrix/matrix_eigen_v.h"


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
    matrixio_show(matrix.content, matrix.rows, matrix.cols);

    __flag_err flags = matrix_check_dimensions(matrix);
    if (flags) {
        pmerror("main():", flags);
        matrixio_free(matrix);
        exit(EXIT_FAILURE);
    }

    Matrix_Eigen_V ev = matrix_inverse_potence_method(matrix);
    if (ev.err) {
        pmerror("matrix_inverse_potence_method():", ev.err);
    }


    printf("Min Eigen Value: %lf\n", ev.eigen_value);
    puts("Eigen Vector:");
    for (int i = 0; i < matrix.rows; i++) {
        printf("%.20lf ", ev.eigen_vector[i]);
    }
    puts("");

    matrixio_free(matrix);
    free(ev.eigen_vector);

    return 0;
}

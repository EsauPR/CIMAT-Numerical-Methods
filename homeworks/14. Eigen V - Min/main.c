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

    Matrix_Eigen_V ev = matrix_eigen_potence_method_inverse(matrix);
    if (ev.err) {
        nsperror("matrix_eigen_potence_method_inverse():", ev.err);
    }


    printf("Min Eigen Value: %.20lf\n", ev.eigen_value);
    puts("Eigen Vector:");
    for (int i = 0; i < matrix.rows; i++) {
        printf("%.20lf ", ev.eigen_vector[i]);
    }
    puts("");

    matrixio_free_matrix(matrix);
    free(ev.eigen_vector);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "numsys/matrix/matrix_sparse.h"

NSMatrixSparse read(const char * file_name) {
    FILE * fd = fopen(file_name, "r");

    int items, rows, cols;

    fscanf(fd, "%d %d %d", &rows, &cols, &items);

    NSMatrixSparse matrix_a = matrix_sparse_create(items+1, rows, cols);

    int r, c;
    double v;
    for (int i = 0; i < items; i++) {
        fscanf(fd, "%d %d %lf", &r, &c, &v);
        matrix_sparse_insert(&matrix_a, r, c, v);
    }

    fclose(fd);

    return matrix_a;
}

// int main(int argc, char const *argv[]) {
int main() {
    // if (argc < 2) {
    //     perror("main():: 2 Args missing");
    //     exit(EXIT_FAILURE);
    // }

    // NSMatrixSparse matrix_a = read(argv[1]);
    // NSMatrixSparse matrix_b = read(argv[1]);
    // NSMatrixSparse matrix_c = matrix_sparse_create(matrix_a.max, matrix_a.ncols, matrix_a.nrows);

    // matrix_sparse_multiply(&matrix_a, &matrix_b, &matrix_c);
    // matrix_sparse_show(matrix_c);

    // matrix_sparse_show(matrix_a);


    NSMatrixSparse matrix_a = matrix_sparse_create(20, 4, 4);
    NSMatrixSparse matrix_b = matrix_sparse_create(20, 4, 4);
    NSMatrixSparse matrix_c = matrix_sparse_create(20, 4, 4);

    matrix_sparse_insert(&matrix_a, 1, 2, 10);
    matrix_sparse_insert(&matrix_a, 1, 4, 12);
    matrix_sparse_insert(&matrix_a, 3, 3, 5);
    matrix_sparse_insert(&matrix_a, 4, 1, 15);
    matrix_sparse_insert(&matrix_a, 4, 2, 12);

    puts("Matrix A");
    matrix_sparse_show(matrix_a);

    matrix_sparse_insert(&matrix_b, 1, 3, 8);
    matrix_sparse_insert(&matrix_b, 2, 4, 23);
    matrix_sparse_insert(&matrix_b, 3, 3, 9);
    matrix_sparse_insert(&matrix_b, 4, 1, 20);
    matrix_sparse_insert(&matrix_b, 4, 2, 25);

    puts("Matrix B");
    matrix_sparse_show(matrix_b);

    puts("Matrix A transpose");
    NSMatrixSparse matrix_at = matrix_sparse_create(matrix_a.max, matrix_a.ncols, matrix_a.nrows);
    matrix_sparse_transpose(&matrix_a, & matrix_at);
    matrix_sparse_show(matrix_at);

    puts("ADD");
    matrix_sparse_add(&matrix_a, &matrix_b, &matrix_c);
    matrix_sparse_show(matrix_c);

    puts("Multiplication");
    NSMatrixSparse matrix_ab = matrix_sparse_create(NS_MAX(matrix_a.max, matrix_b.max), matrix_a.nrows, matrix_b.ncols);
    matrix_sparse_multiply(&matrix_a, &matrix_b, &matrix_ab);
    matrix_sparse_show(matrix_ab);

    double value = 0.0;

    if (matrix_sparse_find_value(matrix_a, 3, 3, &value)) {
        printf("find: %lf\n", value);
    } else {
        puts("no");
    }

    matrix_sparse_free(&matrix_a);
    matrix_sparse_free(&matrix_at);
    matrix_sparse_free(&matrix_b);
    matrix_sparse_free(&matrix_c);
    matrix_sparse_free(&matrix_ab);

    return 0;
}

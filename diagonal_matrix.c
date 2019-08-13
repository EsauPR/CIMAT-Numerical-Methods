/**
    ANSI C standard: c11
    diagonal.cpp
    Purpose: Solve a diagonal matrix

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include "matrix.c"


/* Compute the determinant for a diagonal matrix */
double get_diagonal_matrix_determinant(double **matrix, int size) {
    double determinant = 1.0;

    for (int i = 0; i < size; i++) {
        determinant *= matrix[i][i];
    }

    return determinant;
}

/* Return array with the solution for a diagonal matrix */
double *solve(double **matrix, int size) {
    double * result = create_dynamic_array(size);
    for (int i = 0; i < size; i++) {
        result[i] = matrix[i][size] / matrix[i][i];
    }

    return result;
}

/* Read a augmented square matrix  */
double **read_augmented_square_matrix(int size) {
    double **matrix = create_square_augmented_matrix(size);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j <= size; j++) {
            scanf("%lf", &matrix[i][j]);
        }
    }

    return matrix;
}

/* Print the matrix solution */
void print_result(double *result, int size) {
    for (int i = 0; i < size; i++){
        printf("X_%d = %lf\n", i + 1, result[i]);
    }
    puts("");
}

int main(int argc, char const *argv[]) {
    int size;

    scanf("%d", &size);

    double **matrix = read_augmented_square_matrix(size);
    print_matrix(matrix, size, size + 1);

    double *result = solve(matrix, size);
    print_result(result, size);

    printf("Determinant: %lf\n", get_diagonal_matrix_determinant(matrix, size));

    free_squared_augmented_matriz(matrix, size);
    free(result);

    return 0;
}

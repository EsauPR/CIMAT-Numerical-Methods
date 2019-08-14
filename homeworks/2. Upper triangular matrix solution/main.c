/**
    ANSI C standard: c11
    Purpose: Solve a upper triangular matrix

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include "../../src/matrix.c"
#include "../../src/linear_equations_systems_solutions/backward_substitution.c"


int main(int argc, char const *argv[]) {
    int size;

    scanf("%d", &size);

    double **matrix = read_augmented_square_matrix(size);
    print_matrix(matrix, size, size + 1);

    double *result = solve_upper_triangular_matrix(matrix, size);
    print_result(result, size);

    printf("Determinant: %lf\n", get_diagonal_determinant(matrix, size));

    free_squared_augmented_matriz(matrix, size);
    free(result);

    return 0;
}

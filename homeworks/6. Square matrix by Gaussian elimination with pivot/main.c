/**
    ANSI C standard: c11
    Purpose: Solve a square matrix by Gaussian elimination

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include "../../src/matrix.h"
#include "../../src/linear_equations_systems_solutions/gaussian_elimination.h"


int main(int argc, char const *argv[]) {
    int size;

    scanf("%d", &size);

    double **matrix = read_augmented_square_matrix(size);
    print_matrix(matrix, size, size + 1);

    double *result = solve_by_simple_gaussian_elimination(matrix, size);

    if (result == NULL) {
        puts("The sysyem has not a unique solution");
        return 0;
    }

    print_result(result, size);

    printf("Determinant: %lf\n", get_diagonal_determinant(matrix, size));

    free_squared_augmented_matriz(matrix, size);
    free(result);

    return 0;
}

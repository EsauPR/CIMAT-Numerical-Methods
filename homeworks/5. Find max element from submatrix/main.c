/**
    ANSI C standard: c11
    Purpose: Solve a square matrix by Gaussian elimination

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include "../../src/matrix.h"


int main() {
    int size;

    scanf("%d", &size);

    double **matrix = read_matrix(size, size);
    print_matrix(matrix, size, size);

    MatrixElement mp = find_matrix_max_element(matrix, 0, 0, size - 1, size - 1);

    printf("El elemento con mayor valor obsoluto es: %lf, en (%d, %d)\n", mp.value, mp.row + 1, mp.col + 1);

    free_matriz(matrix, size);

    return 0;
}

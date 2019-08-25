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
    if (argc < 2) {
        perror("main():: 1 Args missing");
        exit(EXIT_FAILURE);
    }

    Matrix matrix = matrixio_read(argv[1]);
    matrixio_show(matrix.content, matrix.rows, matrix.cols);

    MatrixElement mp = matrix_find_max_element(matrix.content, 0, matrix.rows, 0, matrix.cols);
    printf("El elemento con mayor valor obsoluto es: %lf, en (%d, %d)\n", mp.value, mp.row + 1, mp.col + 1);

    matrixio_free(matrix);

    return 0;
}

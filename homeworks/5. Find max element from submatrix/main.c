/**
    ANSI C standard: c11
    Purpose: Find the max element from a matrix

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdlib.h>
#include "numsys/matrix/matrixio.h"
#include "numsys/matrix/matrix.h"


int main(int argc, char *argv[]) {
    if (argc < 2) {
        perror("main():: 1 Args missing");
        exit(EXIT_FAILURE);
    }

    NSMatrix matrix = matrixio_fread_matrix(argv[1]);
    matrixio_show_matrix(matrix);

    NSMatrixElem mp = matrix_find_max_element(matrix.items, 0, matrix.rows, 0, matrix.cols, NS__MATRIX_OPS_NONE_);
    printf("The element with the highest absolute value is: %lf, in (%d, %d)\n", mp.value, mp.row + 1, mp.col + 1);

    matrixio_free_matrix(& matrix);

    return 0;
}

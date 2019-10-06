
/**
    ANSI C standard: c11
    Purpose: Make the sum of two vector in parallel

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#include "../memory.h"

void matrix_matriz_mult(double * a, double * b, double * c, int size) {

    #pragma parallel for
    for (int i = 0; i < size * size; i++) {
        c[i] = 0;
    }


    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        for (int k = 0; k < size; k++) {
            // #pragma omp parallel for
            for (int j = 0; j < size; j++) {
                c[i * size + j] += a[i * size + k] * b[k * size + j];
            }
        }
    }
}


int main(int argc, char const *argv[]) {
    if (argc < 3) {
        puts("Args: [Vector size] [num threads] missing");
        exit(EXIT_FAILURE);
    }

    int size = atoi(argv[1]);
    int threads = atoi(argv[2]);

    omp_set_num_threads(threads);
    double * mat_a = create_array(size * size);
    double * mat_b = create_array(size * size);
    double * mat_c = create_array(size * size);

    matrix_matriz_mult(mat_a, mat_b, mat_c, size);

    free_array(mat_a);
    free_array(mat_b);
    free_array(mat_c);

    return 0;
}

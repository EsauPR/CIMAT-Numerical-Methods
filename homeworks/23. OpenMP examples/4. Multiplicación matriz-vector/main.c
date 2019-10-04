
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

void matrix_vector_mult(double * a, double * b, double * c, int size) {
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        double sum = 0;
        for (int j = 0; j < size; j++) {
            sum += a[i * size + j] * b[j];
        }
        c[i] = sum;
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
    double * vec_b = create_array(size);
    double * vec_c = create_array(size);

    matrix_vector_mult(mat_a, vec_b, vec_c, size);

    free_array(mat_a);
    free_array(vec_b);
    free_array(vec_c);

    return 0;
}

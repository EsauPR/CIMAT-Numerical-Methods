
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

void vector_sum_parallel(double * vec_a, double * vec_b, double * vec_c, int size) {
    #pragma omp parallel for
    for (int i = 0; i < size; ++i) {
        vec_c[i] = vec_a[i] + vec_b[i];
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

    double * vec_a = create_array(size);
    double * vec_b = create_array(size);
    double * vec_c = create_array(size);

    vector_sum_parallel(vec_a, vec_b, vec_c, size);

    free_array(vec_a);
    free_array(vec_b);
    free_array(vec_c);

    return 0;
}

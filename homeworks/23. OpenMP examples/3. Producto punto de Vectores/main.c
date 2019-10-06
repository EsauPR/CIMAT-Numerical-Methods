
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

double vector_scalar_product(double * vec_a, double * vec_b, int size) {
    int res = 0;

    #pragma omp parallel for reduction(+:res)
    for (int i = 0; i < size; ++i) {
        res += vec_a[i] * vec_b[i];
    }

    return res;
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

    vector_scalar_product(vec_a, vec_b, size);

    free_array(vec_a);
    free_array(vec_b);

    return 0;
}

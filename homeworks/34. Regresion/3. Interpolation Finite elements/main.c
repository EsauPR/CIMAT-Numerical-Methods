/**
    ANSI C standard: c11
    main.c
    Purpose: Cuadratic Regresion

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include "numsys/matrix/matrixio.h"
#include "numsys/interpolation/finite_element.h"



int main(int argc, char * argv[]) {
    if (argc < 4) {
        puts("Missing args");
        return 0;
    }

    // Read params
    NSVector x = matrixio_fread_vector(argv[1]);
    NSVector y = matrixio_fread_vector(argv[2]);
    int partition_size = atoi(argv[3]);
    double lambda = atof(argv[4]);

    NSVector z, phi;
    interpolation_finite_elements(x, y, &z, &phi, partition_size, lambda);


    FILE * fsamples = fopen("./output.txt", "w");
    for (int i = 0; i < z.size; i++) {
        fprintf(fsamples, "%f %lf\n", z.items[i], phi.items[i]);
    }

    fclose(fsamples);

    matrixio_free_vector(&x);
    matrixio_free_vector(&y);
    matrixio_free_vector(&z);
    matrixio_free_vector(&phi);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

/*Create the memory for a array*/
double * create_array(int size) {
    double * dinmem = (double *)malloc(size * sizeof(double));
    if (dinmem == NULL) {
        perror("create_array(): ");
        exit(EXIT_FAILURE);
    }
    return dinmem;
}

/* Liberate the memory allocate for a array */
void free_array(double * array) {
    free(array);
}

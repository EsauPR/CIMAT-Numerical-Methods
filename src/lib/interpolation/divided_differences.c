/**
    ANSI C standard: c11
    newton.c
    Purpose: Module to compute the divided diferences

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <stdlib.h>
#include "string.h"

#define NS_DIVIDED_DIFFERENCES_IMPORT
#include "numsys/matrix/matrix.h"
#include "numsys/interpolation/divided_differences.h"

/* Return the coefficients of Newton divided Differences to make interpolations */
double * get_newton_devided_differences(double * x, double *  y, int n) {
    double * diff_table[2] = {matrixio_allocate_array_double(n), matrixio_allocate_array_double(n)};
    double * diffs = matrixio_allocate_array_double(n);

    memcpy(diff_table[0], y, n * sizeof(double));
    diffs[0] = y[0];

    for (int i = 0, row = 0, size = n; i < n-1; i++, size--) {
        for (int j = 0, index = 0; j < size -1; j++, index++) {
            diff_table[(row+1)%2][index] = (diff_table[row][j+1] - diff_table[row][j]) / (x[index+i+1] - x[index]);
        }
        diffs[i+1] = diff_table[(row+1)%2][0];
        row = (row + 1) % 2;
    }

    free(diff_table[0]);
    free(diff_table[1]);

    return diffs;
}

/* Return the coefficients of Forward Differences to make interpolations */
double * get_forward_differences(double * y, int n) {
    double * diff_table[2] = {matrixio_allocate_array_double(n), matrixio_allocate_array_double(n)};
    double * diffs = matrixio_allocate_array_double(n);

    memcpy(diff_table[0], y, n * sizeof(double));
    diffs[0] = y[0];

    for (int i = 0, size = n, row = 0; i < n-1; i++, size--) {
        for (int j = 0, index = 0; j < size-1; j++, index += 1) {
            diff_table[(row+1)%2][index] = (diff_table[row][j+1] - diff_table[row][j]);
        }

        diffs[i+1] = diff_table[(row+1)%2][0];
        row = (row + 1) % 2;
    }

    free(diff_table[0]);
    free(diff_table[1]);

    return diffs;
}

/* Return the coefficients of Backward Differences to make interpolations */
double * get_backward_differences(double * y, int n) {
    double * diff_table[2] = {matrixio_allocate_array_double(n), matrixio_allocate_array_double(n)};
    double * diffs = matrixio_allocate_array_double(n);

    memcpy(diff_table[0], y, n * sizeof(double));
    diffs[0] = y[n-1];

    for (int i = 0, size = n, row = 0; i < n-1; i++, size--) {
        int index = 0;
        for (int j = 0; j < size-1; j++, index += 1) {
            diff_table[(row+1)%2][index] = (diff_table[row][j+1] - diff_table[row][j]);
        }
        diffs[i+1] = diff_table[(row+1)%2][index-1];
        row = (row + 1) % 2;
    }

    free(diff_table[0]);
    free(diff_table[1]);

    return diffs;
}

/* Return the coefficients of Forward Central Differences to make interpolations */
double * get_forward_central_differences(double * y, int n) {
    double * diff_table[2] = {matrixio_allocate_array_double(n), matrixio_allocate_array_double(n)};
    double * diffs = matrixio_allocate_array_double(n);

    memcpy(diff_table[0], y, n * sizeof(double));
    diffs[0] = y[n / 2];

    for (int i = 0, size = n, row = 0; i < n-1; i++) {
        for (int j = 0, index = 0; j < size-1; j++, index += 1) {
            diff_table[(row+1)%2][index] = (diff_table[row][j+1] - diff_table[row][j]);
        }
        size--;
        diffs[i+1] = diff_table[(row+1)%2][size/2];
        row = (row + 1) % 2;
    }

    free(diff_table[0]);
    free(diff_table[1]);

    return diffs;
}

/* Return the coefficients of Backward Central Differences to make interpolations */
double * get_backward_central_differences(double * y, int n) {
    double * diff_table[2] = {matrixio_allocate_array_double(n), matrixio_allocate_array_double(n)};
    double * diffs = matrixio_allocate_array_double(n);

    memcpy(diff_table[0], y, n * sizeof(double));
    diffs[0] = y[(n-1) / 2];

    for (int i = 0, size = n, row = 0; i < n-1; i++) {
        for (int j = 0, index = 0; j < size-1; j++, index += 1) {
            diff_table[(row+1)%2][index] = (diff_table[row][j+1] - diff_table[row][j]);
        }
        size--;
        diffs[i+1] = diff_table[(row+1)%2][(size-1) / 2];
        row = (row + 1) % 2;
    }

    free(diff_table[0]);
    free(diff_table[1]);

    return diffs;
}

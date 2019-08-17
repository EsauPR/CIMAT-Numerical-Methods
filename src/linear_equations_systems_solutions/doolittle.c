/**
    ANSI C standard: c11
    {file}.c
    Purpose: {Description}

   @author Esaú Peralta
   @email esau.opr@gmail.com
*/

#include <stdio.h>
#include "../matrix.h"

#define DOOLITTLE_IMPORT
#include "doolittle.h"


SystemSolution solve_by_doolittle_method(double **matrix, int size) {
    SystemSolution system_solution;
    system_solution.solution = NULL;
    system_solution.determinat = matrix[0][0];

    for (int i = 1; i < size; i++) {
        matrix[i][0] /= matrix[0][0];
    }

    for (int i = 1; i < size; i++) {
        for (int j = 1; j < size; j++) {
            int limit = (j < i) ? j:i;
            for (int k = 0; k < limit; k++) {
                matrix[i][j] -= matrix[i][k] * matrix[k][j];
            }

            if (j < i) {
                matrix[i][j] /= matrix[j][j];
            }
        }

        system_solution.determinat *= matrix[i][i];
    }

    print_matrix(matrix, size, size);

    return system_solution;
}

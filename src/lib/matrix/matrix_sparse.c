/**
    ANSI C standard: c11
    matrix.cpp
    Purpose: Contains helper to create a liberate dinamic sparse matrices

    @author Esaú Peralta
    @email esau.opr@gmail.com

    @references: https://www.geeksforgeeks.org/operations-sparse-matrices/
*/

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "numsys/matrix/matrixio.h"
#include "numsys/matrix/matrix.h"

#define MATRIX_SPARSE_IMPORT
#include "numsys/matrix/matrix_sparse.h"

static void reset_matrix(NSMatrixSparse * matrix) {
    memset(matrix->cols, 0, sizeof(int) * matrix->max);
    memset(matrix->rows, 0, sizeof(int) * matrix->max);
    memset(matrix->values, 0, sizeof(double) * matrix->max);

    matrix->length = 0;
}

NSMatrixSparse matrix_sparse_create(int max, int rows, int cols) {
    NSMatrixSparse matrix = NSMatrixSparseDefault;
    matrix.max = max;
    matrix.nrows = rows;
    matrix.ncols = cols;

    matrix.rows = matrixio_allocate_array_int(max);
    matrix.cols = matrixio_allocate_array_int(max);
    matrix.values = matrixio_allocate_array_double(max);

    return matrix;
}

void matrix_sparse_insert(NSMatrixSparse * matrix, int row, int col, double value) {
    if (row > matrix->nrows || col > matrix->ncols) {
        nsperror("Invalid entry size", NS__MATRIX_ERR_NONE__);
        return;
    }

    matrix->rows[matrix->length] = row;
    matrix->cols[matrix->length] = col;
    matrix->values[matrix->length] = value;
    matrix->length ++;
}

void matrix_sparse_add(NSMatrixSparse * A, NSMatrixSparse * B, NSMatrixSparse * C) {
    if (A->nrows != B->nrows || A->ncols != B->ncols) {
        nsperror("Invalid matrices dimentions", NS__MATRIX_ERR_NONE__);
    }

    int apos = 0, bpos = 0;
    reset_matrix(C);

    while (apos < A->length && bpos < B->length) {
        // if b's row and col is smaller
        if (A->rows[apos] > B->rows[bpos] || (A->rows[apos] == B->rows[bpos] && A->cols[apos] > B->cols[bpos])) {
            // insert smaller value into result
            matrix_sparse_insert(C, B->rows[bpos], B->cols[bpos], B->values[bpos]);
            bpos++;
        }
        // if a's row and col is smaller
        else if (A->rows[apos] < B->rows[bpos] || (A->rows[apos] == B->rows[bpos] && A->cols[apos] < B->cols[bpos])) {
            // insert smaller value into result
            matrix_sparse_insert(C, A->rows[apos], A->cols[apos], A->values[apos]);
            apos++;
        }
        else {
            // add the values as row and col is same
            int addedval = A->values[apos] + B->values[bpos];
            if (addedval != 0) {
                matrix_sparse_insert(C, A->rows[apos], A->cols[apos], addedval);
            }
            // then insert
            apos++;
            bpos++;
        }
    }

    // insert remaining elements
    while (apos < A->length) {
        matrix_sparse_insert(C, A->rows[apos], A->cols[apos], A->values[bpos]);
        bpos++;
    }

    while (bpos < B->length) {
        matrix_sparse_insert(C, B->rows[bpos], B->cols[bpos], B->values[bpos]);
        bpos++;
    }
}


void matrix_sparse_transpose(NSMatrixSparse * matrix, NSMatrixSparse * transpose) {
    // NS_SWAP(matrix->cols, matrix->rows, int *);
    // NS_SWAP(matrix->ncols, matrix->nrows, int);

    // new matrix with inversed row X col
    // same number of elements
    transpose->length = matrix->length;
    // to count number of elements in each column
    int * count = matrixio_allocate_array_int(matrix->ncols+1);

    for (int i = 0; i < matrix->length; i++) {
        count[matrix->cols[i]]++;
    }

    int * index = matrixio_allocate_array_int(matrix->ncols+1);

    // to count number of elements having col smaller
    // than particular i

    // as there is no col with value < 1
    index[1] = 0;

    // initialize rest of the indices
    for (int i = 2; i <= matrix->ncols; i++) {
        index[i] = index[i - 1] + count[i - 1];
    }

    for (int i = 0; i < matrix->length; i++) {

        // insert a data at rpos and increment its value
        int rpos = index[matrix->cols[i]]++;
        // transpose row=col
        transpose->rows[rpos] = matrix->cols[i];
        // transpose col=row
        transpose->cols[rpos] = matrix->rows[i];
        // same value
        transpose->values[rpos] = matrix->values[i];
    }

    // the above method ensures
    // sorting of transpose matrix
    // according to row-col value
    free(count);
    free(index);
}


void matrix_sparse_multiply(NSMatrixSparse * A, NSMatrixSparse * B, NSMatrixSparse * C) {
    if (A->ncols != B->ncols) {
        nsperror("Invalid matrices dimentions", NS__MATRIX_ERR_NONE__);
        return;
    }

    // transpose b to compare row
    // and col values and to add them at the end
    NSMatrixSparse BT = matrix_sparse_create(B->max, B->ncols, B->nrows);
    matrix_sparse_transpose(B, &BT);
    B = &BT;

    int apos, bpos;

    // result matrix of dimension row X b.col
    // however b has been transposed, hence row X b.row
    reset_matrix(C); // size A->nrows, B->nrows

    // iterate over all elements of A
    for (apos = 0; apos < A->length;) {

        // current row of result matrix
        int r = A->rows[apos];

        // iterate over all elements of B
        for (bpos = 0; bpos < B->length;) {

            // current column of result matrix
            // data[][0] used as b is transposed
            int c = B->rows[bpos];

            // temporary pointers created to add all
            // multiplied values to obtain current
            // element of result matrix
            int tempa = apos;
            int tempb = bpos;

            int sum = 0;

            // iterate over all elements with
            // same row and col value
            // to calculate result[r]
            while (tempa < A->length && A->rows[tempa] == r
                    && tempb < B->length && B->rows[tempb] == c) {

                if (A->cols[tempa] < B->cols[tempb])

                    // skip a
                    tempa++;

                else if (A->cols[tempa] > B->cols[tempb])

                    // skip b
                    tempb++;
                else

                    // same col, so multiply and increment
                    sum += A->values[tempa++] * B->values[tempb++];
            }

            // insert sum obtained in result[r]
            // if its not equal to 0
            if (sum != 0) {
                matrix_sparse_insert(C, r, c, sum);
            }

            while (bpos < B->length && B->rows[bpos] == c) {
                // jump to next column
                bpos++;
            }
        }

        while (apos < A->length && A->rows[apos] == r) {
            // jump to next row
            apos++;
        }
    }

    matrix_sparse_free(&BT);
}


void matrix_sparse_show(NSMatrixSparse matrix) {
    printf("Dimension: %d %d\n", matrix.nrows, matrix.ncols);
    printf("Sparse Matrix: \nRow Column Value\n");
    for (int i = 0; i < matrix.length; i++) {
        printf("%d %d %lf\n", matrix.rows[i], matrix.cols[i], matrix.values[i]);
    }
}


int matrix_sparse_find_value(NSMatrixSparse matrix, int row, int col, double * result) {
    int i=0, j = matrix.length -1, middle = 0;

    *result = 0.0;

    while (i <= j) {
        middle = (i + j) / 2;

        if (matrix.rows[middle] == row && matrix.cols[middle] == col ) {
            *result = matrix.values[middle];
            return 1;
        }

        if (matrix.rows[middle] < row) {
            i = middle + 1;
        } else if (matrix.rows[middle] > row) {
            j = middle - 1;
        } else {
            if (matrix.cols[middle] < col) {
                i = middle + 1;
            } else if (matrix.cols[middle] > col) {
                j = middle - 1;
            }
        }
    }

    return 0;
}


void matrix_sparse_free(NSMatrixSparse * matrix) {
    free(matrix->rows);
    free(matrix->cols);
    free(matrix->values);
    matrix->length = 0;
}

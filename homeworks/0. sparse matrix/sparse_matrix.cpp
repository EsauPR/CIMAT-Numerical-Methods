#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;


#define __MATRIX_SPARSE vector<map<int, double> >
#define MATRIX_SPARSE_VIT vector<map<int, double> >::iterator
#define MATRIX_SPARSE_MIT map<int, double>::iterator

typedef struct sparse_matrix {
    __MATRIX_SPARSE items;
    int rows;
    int cols;
} SparseMatrix;


SparseMatrix matrix_sparse_create(int rows, int cols) {
    SparseMatrix matrix;
    matrix.rows = rows;
    matrix.cols = cols;
    matrix.items.resize(rows + 1);
    return matrix;
}


void matrix_sparse_insert(SparseMatrix & matrix, int row, int col, int value) {
    matrix.items[row][col] = value;
}


SparseMatrix matrix_sparse_multiply(SparseMatrix a, SparseMatrix b) {
    SparseMatrix c = matrix_sparse_create(a.rows, b.cols);

    int i = 0;
    for (MATRIX_SPARSE_VIT a_i = a.items.begin(); a_i != a.items.end(); a_i++, i++) {
        map<int, double> * c_i = &(c.items[i]);
        for (MATRIX_SPARSE_MIT a_ik = a_i->begin(); a_ik != a_i->end(); a_ik++) {
            int k = a_ik->first;
            map<int, double> * b_k = &(b.items[k]);
            for (MATRIX_SPARSE_MIT b_kj = b_k->begin(); b_kj != b_k->end(); b_kj++) {
                int j = b_kj->first;
                (*c_i)[j] += a_ik->second * b_kj->second;
            }
        }
    }

    return c;
}

void matrix_sparse_show(SparseMatrix & matrix) {
    printf("Dimension: %d %d\n", matrix.rows, matrix.cols);
    printf("Sparse Matrix: \nRow Column Value\n");
    for (uint i = 0; i < matrix.items.size(); i++) {
        for(MATRIX_SPARSE_MIT it = matrix.items[i].begin(); it != matrix.items[i].end(); it++) {
            printf("%d %d %lf\n", i, it->first, it->second);
        }
    }
}

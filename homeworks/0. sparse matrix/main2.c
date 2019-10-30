#include <iostream>
#include "./sparse_matrix.cpp"

using namespace std;

int main(int argc, char const *argv[]) {

    SparseMatrix matrix_a = matrix_sparse_create( 4, 4);
    SparseMatrix matrix_b = matrix_sparse_create( 4, 4);

    matrix_sparse_insert(matrix_a, 1, 2, 10);
    matrix_sparse_insert(matrix_a, 1, 4, 12);
    matrix_sparse_insert(matrix_a, 3, 3, 5);
    matrix_sparse_insert(matrix_a, 4, 1, 15);
    matrix_sparse_insert(matrix_a, 4, 2, 12);

    puts("Matrix A");
    matrix_sparse_show(matrix_a);

    matrix_sparse_insert(matrix_b, 1, 3, 8);
    matrix_sparse_insert(matrix_b, 2, 4, 23);
    matrix_sparse_insert(matrix_b, 3, 3, 9);
    matrix_sparse_insert(matrix_b, 4, 1, 20);
    matrix_sparse_insert(matrix_b, 4, 2, 25);

    puts("Matrix B");
    matrix_sparse_show(matrix_b);

    SparseMatrix matrix_c = matrix_sparse_multiply(matrix_a, matrix_b);
    puts("Matrix C");
    matrix_sparse_show(matrix_c);

    return 0;
}

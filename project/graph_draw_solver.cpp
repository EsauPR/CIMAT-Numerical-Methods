/**
    C++, standard: c++11
    grap_draw_solver.cpp
    Purpose: Module description

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <ctime>
#include <cmath>
#include <algorithm>
#include <vector>
#include <cstring>

#include "numsys/solvers/cholesky.h"
#include "numsys/solvers/conjugate_gradient.h"
#include "numsys/solvers/doolittle.h"
#include "numsys/solvers/gauss_seidel.h"
#include "numsys/solvers/jacobi.h"
#include "numsys/matrix/matrix.h"
#include "numsys/matrix/matrix_core.h"
#include "numsys/matrix_op/matrix_ldlt.h"
#include "numsys/solvers/bwfw_substitution.h"
#include "numsys/matrix_op/matrix_lu.h"

#define GRAPH_DRAW_SOLVER_IMPORT
#include "graph_draw_solver.hpp"

static NSMatrix _get_distances(vector<pair<pair<int, int>, double>> graph, int n_nodes) {
    NSMatrix distances = matrixio_allocate_matrix(n_nodes, n_nodes);

    // Set the matrix distance to inf
    // double INF = 10e9;
    for (int i = 0; i < n_nodes; i++) {
        for (int j = 0; j < n_nodes; j++) {
            distances.items[i][j] = n_nodes + 5;
        }
        // distances.items[i][i] = 1;
    }

    // Set the distance for connected nodes to 1
    vector<pair<pair<int, int>, double>>::iterator it;
    for (it =  graph.begin(); it != graph.end(); it++) {
        distances.items[it->first.first][it->first.second] = 1;
        distances.items[it->first.second][it->first.first] = 1;
    }

    // Floyd Warshall algorithm to get each distance for each pair of nodes
    #pragma omp parallel for
    for (int k = 0; k < n_nodes; k++) {
        for (int i = 0; i < n_nodes; i++){
            for (int j = 0; j < n_nodes; j++) {
                distances.items[i][j] = min(distances.items[i][j], distances.items[i][k] + distances.items[k][j]);
            }
        }
    }

    // matrixio_show_matrix(distances);

    return distances;
}


static NSMatrix _get_delta_matrix(NSMatrix distances) {
    NSMatrix delta_matrix = matrixio_allocate_matrix(distances.rows, distances.cols);
    // delta_ij = w_ij * d_ij
    #pragma omp parallel for
    for (int i = 0; i < distances.rows; i++) {
        for (int j = 0; j < distances.cols; j++) {
            delta_matrix.items[i][j] = pow(distances.items[i][j], -2.0) * distances.items[i][j];
        }
    }

    // matrixio_show_matrix(delta_matrix);

    return delta_matrix;
}


static NSMatrix _get_laplacian_w_matrix(NSMatrix distances) {
    NSMatrix laplacian_matrix = matrixio_allocate_matrix(distances.rows, distances.cols);
    #pragma omp parallel for
    for (int i = 0; i < distances.rows; i++) {
        for (int j = 0; j < distances.cols; j++) {
            if (i!=j) {
                laplacian_matrix.items[i][j] = - pow(distances.items[i][j], -2.0);
                continue;
            }
            double sum = 0.0;
            for (int k = 0; k < distances.cols; k++) {
                if (i==k) continue;
                sum += pow(distances.items[i][k], -2.0);
            }
            laplacian_matrix.items[i][j] = sum;
        }
    }

    // puts("Lw");
    // matrixio_show_matrix(laplacian_matrix);
    return laplacian_matrix;
}

static void _get_laplacian_z_matrix(NSMatrix Lz, NSMatrix X, NSMatrix delta_matrix) {
    int rows = delta_matrix.rows, cols = delta_matrix.cols;
    #pragma omp parallel for
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i==j) continue;
            double norm = sqrt((X.items[0][i] - X.items[0][j]) * (X.items[0][i] - X.items[0][j]) + (X.items[1][i] - X.items[1][j]) * (X.items[1][i] - X.items[1][j]));
            if (NS_IS_ZERO(norm)) {
                Lz.items[i][j] = 0;
            } else {
                Lz.items[i][j] = -pow(delta_matrix.items[i][j], -2.0) * delta_matrix.items[i][j] / norm;
            }
        }
    }

    #pragma omp parallel for
    for (int i = 0; i < rows; i++) {
        double sum = 0.0;
        for (int k = 0; k < cols; k++) {
            if (i==k) continue;
            sum += Lz.items[i][k];
        }
        Lz.items[i][i] = -sum;
    }

    // puts("Lz");
    // matrixio_show_matrix(Lz);
}


static NSMatrix _graph_build_layout_matrix(int n_nodes) {
    // denote a d-dimensional layout by an n × d matrix X
    // Where n is the number of nodes and d the dimensionnality
    NSMatrix layout = matrixio_allocate_matrix(2, n_nodes);

    srandom(time(NULL));
    #pragma omp parallel for
    for (int i = 0; i < n_nodes; i++) {
        layout.items[0][i] = (double)random() / RAND_MAX;
        layout.items[1][i] = (double)random() / RAND_MAX;
    }

    // Scale and ortogonalize
    for (int k = 0; k < 2; k++) {
        double sum = 0.0;
        double * pntr = layout.items[k];
        for (int i = 0; i < n_nodes; i++) {
            sum += *pntr++;
        }
        sum /= n_nodes;
        pntr = layout.items[k];
        for (int i = 0; i < n_nodes; i++) {
            *pntr++ -= sum;
        }
    }

    matrix_normalize_v(layout.items[0], n_nodes);
    matrix_normalize_v(layout.items[1], n_nodes);

    // puts("layout");
    // matrixio_show_matrix(layout);

    return layout;
}


static double stress(NSMatrix distances, NSMatrix X) {
    int size = distances.rows;
    double _stress = 0.0;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            double w_ij = pow(distances.items[i][j], -2);
            double norm = sqrt((X.items[0][i] - X.items[0][j]) * (X.items[0][i] - X.items[0][j]) + (X.items[1][i] - X.items[1][j]) * (X.items[1][i] - X.items[1][j]));
            _stress += w_ij * pow(norm - distances.items[i][j], 2.0);
            // printf("w_ij: %lf  norm: %lf   stress: %lf\n", w_ij, norm, _stress);
        }
    }

    return _stress;
}


NSMatrix graph_layout_solver1(int n_nodes, vector<pair<pair<int, int>, double>> graph, int niters, double tolerance) {
    puts("build X");
    // NSMatrix X = _graph_build_layout_matrix(n_nodes);
    // Try to get a better inicialization of X solution before the gradiente method
    NSMatrix X = graph_layout_solver2(n_nodes, graph, 3, tolerance);
    puts("distances");
    NSMatrix distances = _get_distances(graph, n_nodes);
    puts("Delta");
    NSMatrix delta_matrix = _get_delta_matrix(distances);
    puts("Lw");
    NSMatrix Lw = _get_laplacian_w_matrix(distances);

    NSMatrix Z = matrixio_allocate_matrix(2, n_nodes);
    NSMatrix Lz = matrixio_allocate_matrix(n_nodes, n_nodes);

    NSVector x_axes_tmp = matrixio_allocate_vector(n_nodes);

    NSMatrixSystem msystem = NSMatrixSystemDefault;
    msystem.a = Lw;
    msystem.x = matrixio_allocate_vector(n_nodes);
    msystem.b = matrixio_allocate_vector(n_nodes);


    for (int iter = 0; iter < niters; iter++) {
        printf("step %d\n", iter);

        NS_SWAP(X.items, Z.items, double **);
        NS_SWAP(X.pointer_start, Z.pointer_start, double *);

        _get_laplacian_z_matrix(Lz, Z, delta_matrix);

        for (int axe = 0; axe < 2; axe++) {
            memcpy(x_axes_tmp.items, Z.items[axe], sizeof(double) * n_nodes);
            matrix_multiply_mvd(Lz.items, x_axes_tmp.items, msystem.b.items, Lz.rows, Lz.cols);

            conjugate_gradient_solver(&msystem);

            memcpy(X.items[axe], msystem.x.items, sizeof(double) * n_nodes);
        }

        double stress_xt = stress(distances, Z);
        double stress_xt1 = stress(distances, X);
        double ctol = (stress_xt - stress_xt1) / stress_xt;
        printf("ctol: %le\n", ctol);

        if (iter != 0 && abs(ctol) < tolerance) {
            break;
        }
    }

    matrixio_free_matrix(&Lw);
    matrixio_free_matrix(&delta_matrix);
    matrixio_free_matrix(&Z);
    matrixio_free_matrix(&Lz);
    matrixio_free_matrix(&distances);
    matrixio_free_vector(&x_axes_tmp);
    matrixio_free_vector(&msystem.b);
    matrixio_free_vector(&msystem.x);

    return X;
}


static void solver_make_perm(double * b, int * row_perm_map, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (row_perm_map[i] == i) continue;
        NS_SWAP(b[i], b[row_perm_map[i]], double);
    }
}


NSMatrix graph_layout_solver2(int n_nodes, vector<pair<pair<int, int>, double>> graph, int niters, double tolerance) {
    puts("build X");
    NSMatrix X = _graph_build_layout_matrix(n_nodes);
    puts("distances");
    NSMatrix distances = _get_distances(graph, n_nodes);
    puts("Delta");
    NSMatrix delta_matrix = _get_delta_matrix(distances);
    puts("Lw");
    NSMatrix Lw = _get_laplacian_w_matrix(distances);

    NSMatrix Z = matrixio_allocate_matrix(2, n_nodes);
    NSMatrix Lz = matrixio_allocate_matrix(n_nodes, n_nodes);

    NSVector x_axes_tmp = matrixio_allocate_vector(n_nodes);

    NSMatrixSystem msystem = NSMatrixSystemDefault;
    msystem.a = Lw;
    msystem.x = matrixio_allocate_vector(n_nodes);
    msystem.b = matrixio_allocate_vector(n_nodes);


    int size = msystem.a.rows;
    double **matrix = msystem.a.items;

    int * row_perm_map = matrix_ldlt_decomposition(&(msystem.a));
    solver_make_perm(msystem.b.items, row_perm_map, msystem.b.size);
    free(row_perm_map);

    if (msystem.a.err) {
        msystem.err |= msystem.a.err | NS__MATRIX_ERR_NO_SOLUTION__;
        nsperror((char*)"Error", msystem.err);
        return X;
    }

    // Multiply L x D in the same matrix, this LD is matriz is a lower traingular matrix
    for (int i = 1; i < size; i++) {
        for (int j = 0; j < i; j++){
            matrix[i][j] *= matrix[j][j];
        }
    }

    // puts("LD");
    // matrixio_show_matrix(msystem.a);

    while(niters--) {
        printf("step %d\n", niters);
        NS_SWAP(X.items, Z.items, double **);
        NS_SWAP(X.pointer_start, Z.pointer_start, double *);

        _get_laplacian_z_matrix(Lz, Z, delta_matrix);

        for (int axe = 0; axe < 2; axe++) {
            memcpy(x_axes_tmp.items, Z.items[axe], sizeof(double) * n_nodes);
            matrix_multiply_mvd(Lz.items, x_axes_tmp.items, msystem.b.items, Lz.rows, Lz.cols);

            // Solve Ly = b where L has a diagonal with ones
            solver_forward_substitution(&msystem, NS__MATRIX_OPS_NONE_);
            // Solve Ux = y
            NS_SWAP(msystem.x.items, msystem.b.items, double *);
            solver_backward_substitution(&msystem, NS__MATRIX_OPS_DIAG_HAS_ONES__);

            memcpy(X.items[axe], msystem.x.items, sizeof(double) * n_nodes);
        }

        double stress_xt = stress(distances, Z);
        double stress_xt1 = stress(distances, X);
        double ctol = (stress_xt - stress_xt1) / stress_xt;
        printf("stress: %le %le\n", stress_xt, stress_xt1);
        printf("ctol: %le\n", ctol);

        if (abs(ctol) < tolerance) {
            break;
        }
        // puts("layout");
        // matrixio_show_matrix(X);
    }

    matrixio_free_matrix(&Lw);
    matrixio_free_matrix(&delta_matrix);
    matrixio_free_matrix(&Z);
    matrixio_free_matrix(&Lz);
    matrixio_free_matrix(&distances);
    matrixio_free_vector(&x_axes_tmp);
    matrixio_free_vector(&msystem.b);
    matrixio_free_vector(&msystem.x);

    return X;
}


NSMatrix graph_layout_solver3(int n_nodes, vector<pair<pair<int, int>, double>> graph, int niters, double tolerance) {
    NSMatrix X = _graph_build_layout_matrix(n_nodes);
    NSMatrix distances = _get_distances(graph, n_nodes);
    NSMatrix delta_matrix = _get_delta_matrix(distances);
    NSMatrix Lw = _get_laplacian_w_matrix(distances);

    NSMatrix Z = matrixio_allocate_matrix(2, n_nodes);
    NSMatrix Lz = matrixio_allocate_matrix(n_nodes, n_nodes);

    NSVector x_axes_tmp = matrixio_allocate_vector(n_nodes);

    NSMatrixSystem msystem = NSMatrixSystemDefault;
    msystem.a = Lw;
    msystem.x = matrixio_allocate_vector(n_nodes);
    msystem.b = matrixio_allocate_vector(n_nodes);

    // Uncomment for doolittle
    // int * row_perm_map = matrix_lu_decomposition(&(msystem.a));
    // solver_make_perm(msystem.b.items, row_perm_map, msystem.b.size);
    // free(row_perm_map);

    // if (msystem.a.err) {
    //     msystem.err |= msystem.a.err | NS__MATRIX_ERR_NO_SOLUTION__;
    //     return X;
    // }

    while(niters--) {
        printf("step %d\n", niters);
        NS_SWAP(X.items, Z.items, double **);
        NS_SWAP(X.pointer_start, Z.pointer_start, double *);

        _get_laplacian_z_matrix(Lz, Z, delta_matrix);

        for (int axe = 0; axe < 2; axe++) {
            memcpy(x_axes_tmp.items, Z.items[axe], sizeof(double) * n_nodes);
            matrix_multiply_mvd(Lz.items, x_axes_tmp.items, msystem.b.items, Lz.rows, Lz.cols);

            // solver_doolittle_method_lu(&msystem);
            gauss_seidel_solver(&msystem);
            // jacobi_solver(&msystem);

            memcpy(X.items[axe], msystem.x.items, sizeof(double) * n_nodes);
        }

        double stress_xt = stress(distances, Z);
        double stress_xt1 = stress(distances, X);
        double ctol = (stress_xt - stress_xt1) / stress_xt;
        printf("stress: %le %le\n", stress_xt, stress_xt1);
        printf("ctol: %le\n", ctol);

        if (abs(ctol) < tolerance) {
            break;
        }
    }

    matrixio_free_matrix(&Lw);
    matrixio_free_matrix(&delta_matrix);
    matrixio_free_matrix(&Z);
    matrixio_free_matrix(&Lz);
    matrixio_free_matrix(&distances);
    matrixio_free_vector(&x_axes_tmp);
    matrixio_free_vector(&msystem.b);
    matrixio_free_vector(&msystem.x);

    return X;
}

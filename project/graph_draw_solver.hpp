/**
    C++, standard: c++11
    grap_draw_solver.cpp
    Purpose: Module with the logic to draw a graph

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#ifndef GRAPH_DRAW_SOLVER_H
#include <vector>
#include "numsys/matrix/matrixio.h"

#ifdef GRAPH_DRAW_SOLVER_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

using namespace std;

NSMatrix graph_layout_solver(int n_nodes, vector<pair<pair<int, int>, double>> graph, int niters, double tolerance=0.01);
NSMatrix graph_layout_solver2(int n_nodes, vector<pair<pair<int, int>, double>> graph, int niters, double tolerance=0.01);


#undef GRAPH_DRAW_SOLVER_IMPORT
#undef EXTERN
#endif

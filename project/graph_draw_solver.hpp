/**
    C++, standard: c++11
    grap_draw_solver.cpp
    Purpose: Module with the logic to draw a graph

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/


#ifndef GRAPH_DRAW_SOLVER_H
#include "graphio.hpp"
#include "numsys/matrix/matrixio.h"

#ifdef GRAPH_DRAW_SOLVER_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif


NSMatrix graph_layout_solver(int n_nodes, Graph graph, int width, int hight, int niters);


#undef GRAPH_DRAW_SOLVER_IMPORT
#undef EXTERN
#endif

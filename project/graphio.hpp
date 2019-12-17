/**
    C++, standard: c++11
    graphio.hpp
    Purpose: Module to read and write graphs
    in format MatrixMarket matrix coordinate

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#ifndef GRAPHIO_H

#include <map>
#include <vector>

#ifdef GRAPHIO_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif
using namespace std;

#define Graph vector<pair<pair<int, int>, double>>

Graph graph_read(const string file_name, int * n_nodes, bool has_weight);

#undef GRAPHIO_IMPORT
#undef EXTERN
#endif

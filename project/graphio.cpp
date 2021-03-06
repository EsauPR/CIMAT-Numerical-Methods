/**
    C++, standard: c++11
    graphio.cpp
    Purpose: Module to read and write graphs
    in format MatrixMarket matrix coordinate

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <iostream>
#include <fstream>

using namespace std;

#define GRAPHIO_IMPORT
#include "graphio.hpp"


Graph graph_read(const string file_name, int * n_nodes, bool has_weight) {
    ifstream f_in (file_name);
    if (!f_in.is_open()) {
        cout << "Can't open file: " << file_name << endl;
        exit(EXIT_FAILURE);
    }

    // string comment;
    // getline(f_in, comment);

    int rows, cols, nitems;
    f_in >> rows >> cols >> nitems;
    *n_nodes = rows;

    cout << rows << " " << cols << " " << nitems << endl;

    int node_i, node_j;
    double weight;
    Graph graph;

    while (nitems--) {
        if (has_weight) {
            f_in >> node_i >> node_j >> weight;
            cout << node_i << " " << node_j << " " << weight << endl;
        } else {
            f_in >> node_i >> node_j;
            cout << node_i << " " << node_j << " " << "None" << endl;
        }

        if (node_i == node_j) continue;
        graph.push_back(make_pair(make_pair(node_i - 1, node_j - 1), weight));
    }

    f_in.close();

    return graph;
}

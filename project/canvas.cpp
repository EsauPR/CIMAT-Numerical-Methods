/**
    C++, standard: c++11
    canvas.cpp
    Purpose: Canvas for graph layout

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <vector>
#include <algorithm>
#include <iostream>

#define CANVAS_IMPORT
#include "canvas.hpp"

using namespace std;


CCanvas::CCanvas(Graph graph, double ** layout, int size, int width, int hight) {
    _graph = graph;
    _size = size;

    // _layout = layout;

    vector<vector<double>> laytmp;

    vector<double> tmp1(layout[0], layout[0] + size);
    vector<double> tmp2(layout[1], layout[1] + size);

    laytmp.push_back(tmp1);
    laytmp.push_back(tmp2);
    int offset = 10;

    cout << "Nomalize layout" << endl;

    for (int i = 0; i < 2; i++) {
        double dmin = * min_element(laytmp[i].begin(), laytmp[i].end());
        double dmax = * max_element(laytmp[i].begin(), laytmp[i].end());

        // cout << dmin << " " << dmax << endl;

        double delta = (i==0)? width - offset * 2 : hight - offset * 2;
        delta /= dmax-dmin;
        for (int j = 0; j < size; j++) {
            laytmp[i][j] = laytmp[i][j] * delta + offset - dmin * delta;
            // cout << laytmp[i][j] << " ";
        }
        // cout << endl;
    }

    _layout = laytmp;
}


/* Draw a edge that join two nodes */
void CCanvas::draw_edges(const Cairo::RefPtr<Cairo::Context>& cr) {

    cr->set_line_width(0.5);
    cr->set_source_rgb(1.0, 0.5, 0.0);

    Graph::iterator it;

    for (it = _graph.begin();  it != _graph.end(); it++)  {
        int node_i = it->first.first, node_j = it->first.second;
        cr->move_to(_layout[0][node_i], _layout[1][node_i]);
        cr->line_to(_layout[0][node_j], _layout[1][node_j]);
    }

    cr->stroke();
}


/* Draw the nodes */
void CCanvas::draw_nodes(Cairo::RefPtr<Cairo::Context> const & cr) {
    cr->set_line_width(0.5);
    cr->set_source_rgb(0.3, 0.3, 0.3);

    for (int i = 0; i < _size; i++) {
        cr->arc(_layout[0][i], _layout[1][i], 3, 0, 2 * 3.1416);
        cr->fill();
        cr->stroke();
    }
}


/* Draw draw the graph with the given layout */
bool CCanvas::on_draw(Cairo::RefPtr<Cairo::Context> const & cr) {
    draw_edges(cr);
    draw_nodes(cr);

    return true;
}

/**
    C++, standard: c++11
    canvas.cpp
    Purpose: Canvas for graph layout

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <vector>

#define CANVAS_IMPORT
#include "canvas.hpp"

using namespace std;


CCanvas::CCanvas(Graph graph, double ** layout, int size) {
    _graph = graph;
    _size = size;
    _layout = layout;
}


/* Draw a queen in any cell position */
void CCanvas::draw_edges(const Cairo::RefPtr<Cairo::Context>& cr) {

    cr->set_line_width(2.0);
    cr->set_source_rgb(1.0, 0.5, 0.0);

    Graph::iterator it;

    for (it = _graph.begin();  it != _graph.end(); it++)  {
        int node_i = it->first.first, node_j = it->first.second;
        cr->move_to(_layout[node_i][0], _layout[node_i][1]);
        cr->line_to(_layout[node_j][0], _layout[node_j][1]);
    }

    cr->stroke();
}


/* Draw the board */
void CCanvas::draw_nodes(Cairo::RefPtr<Cairo::Context> const & cr) {
    cr->set_line_width(0.5);
    cr->set_source_rgb(1.0, 0.5, 0.0);

    double _spacing_size = 10.0;

    for (int i = 0; i < _size; i++) {
        cr->rectangle(_layout[i][0] * _spacing_size, _layout[i][1] * _spacing_size , _spacing_size, _spacing_size);
        cr->fill();
        cr->stroke();
    }
}


/* Draw a board and queens for any solution*/
bool CCanvas::on_draw(Cairo::RefPtr<Cairo::Context> const & cr) {
    draw_nodes(cr);
    draw_edges(cr);

    return true;
}

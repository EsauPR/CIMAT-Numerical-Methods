/**
    C++, standard: c++11
    canvas.cpp
    Purpose: Canvas prototype

    @author Esaú Peralta
    @email esau.opr@gmail.com

    @references: https://github.com/morgner/Cairo-Tutorial
*/

#ifndef CANVAS_H

#include <gtkmm.h>
#include <gtkmm/drawingarea.h>
#include <map>

#include <vector>
#include "graphio.hpp"

#ifdef CANVAS_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

using namespace std;

class CCanvas: public Gtk::DrawingArea {
    public:
        CCanvas(Graph graph, double ** layout, int size, int width, int hight);
        virtual ~CCanvas() { };

    private:
        Graph _graph;
        int _size;
        int _scale;
        vector<vector<double>> _layout;

        void draw_nodes(Cairo::RefPtr<Cairo::Context> const & cr);
        void draw_edges(Cairo::RefPtr<Cairo::Context> const & cr);

    protected:
        // Override default signal handler
        bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
};


#undef CANVAS_IMPORT
#undef EXTERN
#endif

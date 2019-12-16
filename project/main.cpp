/**
    ANSI C standard: c11
    main.c
    Purpose: Stress Majorization to draw graphs

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <cstdio>
#include <gtkmm/application.h>
#include <gtkmm/window.h>

#include "numsys/matrix/matrixio.h"
#include "graphio.hpp"
#include "graph_draw_solver.hpp"
#include "canvas.hpp"


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Missing args");
        exit(EXIT_FAILURE);
    }

    int n_nodes = 0;
    Graph graph = graph_read(argv[1], &n_nodes);

    int width = 1024, hight = 768;
    int max_iters = 100;

    NSMatrix layout = graph_layout_solver(n_nodes, graph, width, hight, max_iters);
    // graph_layout_solver(n_nodes, graph, width, hight, max_iters);


    // static auto app = Gtk::Application::create(argc, argv, "org.gtkmm.cairo.tut");

    // Gtk::Window window;
    // window.resize(width, hight);
    // window.set_title("Graph drawing by stress majorization");

    CCanvas c_graph(graph, layout.items, n_nodes);
    // window.add(c_graph);
    // c_graph.show();

    // app->run(window);

    return 0;
}

/**
    ANSI C standard: c11
    main.c
    Purpose: Stress Majorization to draw graphs

    @author Esaú Peralta
    @email esau.opr@gmail.com
*/

#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <gtkmm/application.h>
#include <gtkmm/window.h>

#include "numsys/matrix/matrixio.h"
#include "graphio.hpp"
#include "graph_draw_solver.hpp"
#include "canvas.hpp"


void draw(int argc, char *argv[], Graph graph, NSMatrix layout, int width, int hight) {
    static auto app = Gtk::Application::create(argc, argv, "org.gtkmm.cairo.tut");

    Gtk::Window window;
    window.resize(width, hight);
    window.set_title("Graph drawing by stress majorization");

    CCanvas c_graph(graph, layout.items, layout.rows);
    window.add(c_graph);
    c_graph.show();

    app->run(window);
}

void save_layout(NSMatrix layout) {
    string file_name = "layout.txt";
    ofstream f_out(file_name);
    if (!f_out.is_open()) {
        cout << "Can't not open file: " << file_name;
        return;
    }

    for (int i = 0; i < layout.rows; i++) {
        f_out << i << " " << layout.items[i][0] << " " << layout.items[i][1] << endl;
    }

    f_out.close();
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Missing args");
        exit(EXIT_FAILURE);
    }

    int width = 1024, hight = 768;

    int n_nodes = 0;
    Graph graph = graph_read(argv[1], &n_nodes);

    int max_iters = 30;
    NSMatrix layout = graph_layout_solver2(n_nodes, graph, width, hight, max_iters);

    save_layout(layout);

    draw(1, argv, graph, layout, width, hight);

    return 0;
}

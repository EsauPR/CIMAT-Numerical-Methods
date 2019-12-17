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

    CCanvas c_graph(graph, layout.items, layout.cols, width, hight);
    window.add(c_graph);
    c_graph.show();

    app->run(window);
}

// void save_layout(NSMatrix layout) {
//     string file_name = "layout.txt";

//     FILE * fp = fopen("layout.txt", "w");
//     if (fp == NULL) {
//         cout << "Can't not open file: " << file_name << endl;
//     }

//     for (int i = 0; i < layout.cols; i++) {
//         fprintf(fp, "%4d - %lf %lf\n", i, layout.items[0][i], layout.items[1][i]);
//     }

//     fclose(fp);

//     // string file_name = "layout.txt";
//     // ofstream f_out(file_name);
//     // if (!f_out.is_open()) {
//     //     cout << "Can't not open file: " << file_name << endl;
//     //     return;
//     // }

//     // for (int i = 0; i < layout.cols; i++) {
//     //     f_out << i << " " << layout.items[0][i] << " " << layout.items[1][i] << endl;
//     // }

//     // f_out.close();
// }


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Missing args");
        exit(EXIT_FAILURE);
    }


    string w = (argc >= 3)? argv[2] : "";
    bool has_weight = (w == "-w")? true: false;

    int width = 1024, hight = 768;

    int n_nodes = 0;
    Graph graph = graph_read(argv[1], &n_nodes, has_weight);

    int max_iters = 100;

    NSMatrix layout = graph_layout_solver3(n_nodes, graph, max_iters, 10e-8);

    // cout << "final Layput start" << endl;
    // matrixio_show_matrix(layout);
    // cout << "final Layput end" << endl;
    // save_layout(layout);

    draw(1, argv, graph, layout, width, hight);

    matrixio_free_matrix(&layout);

    return 0;
}

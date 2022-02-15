#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <sstream>

class Graph {
    private:
        Graph *_left;
        Graph *_right;

        char _value;

        int _mode;

        void _print_graph_utils(int current_level, bool side, int *dirswap);
        void _print_graph(int current_level, bool side, int *dirswap);

    public:
        Graph(char value, int mode);
        Graph(Graph &copy);

        int is_leaf();

        int insert(Graph *child);
        int check_graph();

        std::string to_nnf_string();
        std::string to_cnf_string();

        void convert_to_nnf();
        void convert_to_cnf();

        int compute();

        int max_depth();
        void print();

        void free_childs();
        ~Graph();
};

#endif // !GRAPH_HPP
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>

class Graph {
    private:
        Graph *_left;
        Graph *_right;

        char _value;

    public:
        Graph(char value);

        int insert(Graph *child);
        int check_graph();
        int compute();

        ~Graph();
};

#endif // !GRAPH_HPP
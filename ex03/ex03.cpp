#include <stdio.h>
#include <stdbool.h>
#include <iostream>

#include "Graph.hpp"

bool eval_formula(std::string formula) {    
    Graph *root = nullptr;
    
    // Build tree
    for (std::string::reverse_iterator itr = formula.rbegin(); itr != formula.rend(); itr++) {
        Graph *new_graph = new Graph(*itr);
        if (!root)
            root = new_graph;
        else
            root->insert(new_graph);
    }

    // Check graph
    if (!root || root->check_graph()) {
        std::cerr << "\nFormat Error !" << std::endl;
        return (false);
    }

    // Compute result
    char result = root->compute();
    if (result == -1) {
        std::cerr << "\nInvalid characters !" << std::endl;
        return (false);
    }
    return (result);
}

void make_test(std::string test, bool res) {
    int eval = eval_formula(test);
    std::cout << (eval == res ? "\033[1;34m" : "\033[1;35m");
    std::cout << "(" << res << "){" << test << "} => " << eval << "\033[0m\n";
}

int main() {
    make_test("0", false);
    make_test("1", true);

    make_test("0!", true);
    make_test("1!", false);

    make_test("00&", false);
    make_test("10&", false);
    make_test("01&", false);
    make_test("11&", true);
    
    make_test("00|", false);
    make_test("01|", true);
    make_test("10|", true);
    make_test("11|", true);

    make_test("00>", true);
    make_test("01>", true);
    make_test("10>", false);
    make_test("11>", true);

    make_test("00^", false);
    make_test("01^", true);
    make_test("10^", true);
    make_test("11^", false);

    make_test("00=", true);
    make_test("01=", false);
    make_test("10=", false);
    make_test("11=", true);

    make_test("1011||=", true);
    make_test("101!1||=", true);
    make_test("0110|!1||=", false);
    make_test("11011&|!1||=", true);
    make_test("11001^1&|!1||=", true);

    // Invalid format:
    make_test("", false);
    make_test("0d|", false);
    make_test("!1||=", false);
    make_test("10|!1||=", false);
    return (0);
}

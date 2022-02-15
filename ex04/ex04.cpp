#include <stdio.h>
#include <stdbool.h>
#include <map>
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

std::string replace_char(std::string formula, std::map<char, char> &map) {
    std::string new_formula = "";
    for (std::string::iterator itr = formula.begin(); itr != formula.end(); itr++) {
        if (map.find(*itr) != map.end())
            new_formula += map.find(*itr)->second + '0';
        else
            new_formula += *itr;
    }
    return (new_formula);
}

void print_truth_table(std::string formula)
{
    int result;
    std::map<char, char> bool_set;
    std::string formula_copy;
    
    formula_copy = formula;

    // Init
    for (std::string::iterator itr = formula.begin(); itr != formula.end(); itr++)
        if (std::string("ABCDEFGHIJKLMNOPQRSTUVWXYZ!&|>^=").find(*itr) == std::string::npos)
        {
            std::cerr << "Invalid char: " << formula << std::endl;
            return;
        }
        else if (*itr >= 'A' && *itr <= 'Z')
            bool_set.insert(std::pair<char, char>(*itr, 0));

    result = eval_formula(replace_char(formula_copy, bool_set));

    if (formula == "" || result == -1)
    {
        std::cerr << "Invalid formula: " << formula << std::endl;
        return;
    }

    // Print formula
    std::cout << "\n\033[1;34mFormula: " << formula << std::endl;

    // Print header
    std::cout << "\033[1;34m╔═";
    for (std::map<char, char>::iterator itr = bool_set.begin(); itr != bool_set.end(); itr++)
        std::cout << "══╦═";
    std::cout << "══╗\033[0m" << std::endl;
    
    // Print variables
    std::cout << "\033[1;34m║ \033[0m";
    for (std::map<char, char>::iterator itr = bool_set.begin(); itr != bool_set.end(); itr++)
        std::cout << "\033[1;33m" << itr->first << " \033[1;34m║\033[0m ";
    std::cout << "\033[1;33m= \033[1;34m║\033[0m" << std::endl;

    // Print separator
    std::cout << "\033[1;34m╠═";
    for (std::map<char, char>::iterator itr = bool_set.begin(); itr != bool_set.end(); itr++)
        std::cout << "══╬═";
    std::cout << "══╣\033[0m" << std::endl;

    while (true)
    {
        result = eval_formula(replace_char(formula_copy, bool_set));

        // Print result
        std::cout << "\033[1;34m║\033[0m ";
        for (std::map<char, char>::iterator itr = bool_set.begin(); itr != bool_set.end(); itr++)
            std::cout << (itr->second ? "\033[1;32m" : "\033[1;31m") << (char)(itr->second + '0') << " \033[1;34m║\033[0m ";
        std::cout << (result ? "\033[1;32m" : "\033[1;31m") << result << " \033[1;34m║\033[0m" << std::endl;

        // Increment
        for (std::map<char, char>::reverse_iterator itr = bool_set.rbegin(); itr != bool_set.rend(); itr++)
            if (itr->second == 0)
            {
                itr->second = 1;
                break;
            }
            else
                itr->second = 0;
        int all_zero = true;
        for (std::map<char, char>::iterator itr = bool_set.begin(); itr != bool_set.end(); itr++)
            if (itr->second == 1)
                all_zero = false;
        if (all_zero)
            break;
    }
    // Print footer
    std::cout << "\033[1;34m╚═";
    for (std::map<char, char>::iterator itr = bool_set.begin(); itr != bool_set.end(); itr++)
        std::cout << "══╩═";
    std::cout << "══╝\033[0m" << std::endl;
}

int main() {
    print_truth_table("A");
    print_truth_table("B");

    print_truth_table("A!");
    print_truth_table("AB&");
    print_truth_table("AB|");
    print_truth_table("AB>");
    print_truth_table("AB^");
    print_truth_table("AB=");

    print_truth_table("ABCD||=");
    print_truth_table("ABC!D||=");

    print_truth_table("BC|A&");
    print_truth_table("AB&AC&|");

    // Invalid format:
    print_truth_table("");
    print_truth_table("0d|");
    print_truth_table("!1||=");
    print_truth_table("AB|!1||=");
    return (0);
}

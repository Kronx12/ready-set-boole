#ifndef UTILS_HPP
# define UTILS_HPP

# include <map>
# include <iostream>
# include "Graph.hpp"

# ifndef DEBUG
#  define DEBUG 0
# endif

// String manipulation
std::string replace_char(std::string formula, std::map<char, char> &map);

// Graph manipulation
Graph *build_tree(std::string formula);
bool eval_formula(std::string formula);
void print_truth_table(std::string formula);
std::string negation_normal_form(std::string formula);
std::string conjunctive_normal_form(std::string formula);

#endif // !UTILS_HPP
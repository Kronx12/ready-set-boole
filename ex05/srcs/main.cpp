#include <stdio.h>
#include <stdbool.h>
#include <map>
#include <iostream>

#include "utils.hpp"

void make_test(std::string str) {
    std::string result = negation_normal_form(str);

    std::cout << "\033[1;34m" << str << "\033[0m => \033[1;31m" << result << "\033[0m" << std::endl;
}

int main() {
    make_test("A");
    make_test("B");

    make_test("A!");
    make_test("AB&");
    make_test("AB|");
    make_test("AB>");
    make_test("AB^");
    make_test("AB=");

    make_test("ABCD||=");
    make_test("ABC!D||=");

    make_test("BC|A&");
    make_test("AB&AC&|");

    make_test("AB&!");
    make_test("AB|!");
    make_test("AB>");
    make_test("AB=");
    make_test("AB|C&!");

    // Invalid format:
    make_test("");
    make_test("0d|");
    make_test("!1||=");
    make_test("AB|!1||=");
    return (0);
}

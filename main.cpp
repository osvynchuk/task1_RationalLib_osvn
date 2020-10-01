// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// CPP course
// (c) Oleksiy Svynchuk
//
#include <iostream>
#include <set>
#include "rational.h"

void run_some_tests();


int main() {
    try {
        // Input 2 numbers
        rational_t rnum2;
        std::cout << "Input a rational number, in form num/denum: " << std::endl;
        std::cin >> rnum2;
        std::cout << rnum2 << std::endl;

        rational_t rnum3;
        std::cout << "Input a rational number, in form num/denum: " << std::endl;
        std::cin >> rnum3;
        std::cout << rnum3 << std::endl;
        std::cout << std::endl;

        // Operation +
        std::cout << rnum2 << "+" << rnum3 << " = " << rnum2 + rnum3 << std::endl;

        // Operation -
        std::cout << rnum2 << "-" << rnum3 << " = " << rnum2 - rnum3 << std::endl;

        // Operation *
        std::cout << rnum2 << "*" << rnum3 << " = " << rnum2 * rnum3 << std::endl;

        // Operation /
        std::cout << rnum2 << "/" << rnum3 << " = " << rnum2 / rnum3 << std::endl;

        // Operation ==
        std::cout << rnum2 << "==" << rnum3 << " = " << ((rnum2 == rnum3) ? "true" : "false") << std::endl;

        // Operation <
        std::cout << rnum2 << "<" << rnum3 << " = " << ((rnum2 < rnum3) ? "true" : "false") << std::endl;

        // Operation <
        std::cout << rnum2 << ">" << rnum3 << " = " << ((rnum2 > rnum3) ? "true" : "false") << std::endl;

        // Use rational_t with sorted container
        std::set<rational_t> rset {{2,3}, {1,2}, {4,4}};
        std::cout << "set: ";
        for (auto& ent: rset) { std::cout << ent << ", "; }
        std::cout << std::endl;

        // Run tests
        run_some_tests();

    } catch (std::exception& ex) {
        std::cout << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}

void run_some_tests() {
    rational_t rnum1 {1,2};
    rational_t rnum2 {2,3};

    if ((rnum1 + rnum2) != rational_t(7,6))
        throw std::runtime_error("Test case #1 (op+) failed");

    if ((rnum1 - rnum2) != rational_t(-1,6))
        throw std::runtime_error("Test case #2 (op-) failed");

    if ((rnum1 * rnum2) != rational_t(1,3))
        throw std::runtime_error("Test case #3 (op*) failed");

    if ((rnum1 / rnum2) != rational_t(3,4))
        throw std::runtime_error("Test case #4 (op/) failed");

    if ((rnum1 == rnum2) != false)
        throw std::runtime_error("Test case #5 (op==) failed");

    if ((rnum1 < rnum2) != true)
        throw std::runtime_error("Test case #6 (op<) failed");

    // TODO

}

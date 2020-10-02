// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// CPP course
// (c) Oleksiy Svynchuk
//
#include <iostream>
#include <set>
#include <sstream>
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
        std::cout << rnum2 << " + " << rnum3 << " = " << rnum2 + rnum3 << std::endl;

        // Operation -
        std::cout << rnum2 << " - " << rnum3 << " = " << rnum2 - rnum3 << std::endl;

        // Operation *
        std::cout << rnum2 << " * " << rnum3 << " = " << rnum2 * rnum3 << std::endl;

        // Operation /
        std::cout << rnum2 << " / " << rnum3 << " = " << rnum2 / rnum3 << std::endl;

        // Operation ==
        std::cout << rnum2 << "== " << rnum3 << " = " << ((rnum2 == rnum3) ? "true" : "false") << std::endl;

        // Operation !=
        std::cout << rnum2 << "!= " << rnum3 << " = " << ((rnum2 != rnum3) ? "true" : "false") << std::endl;

        // Operation <
        std::cout << rnum2 << " < " << rnum3 << " = " << ((rnum2 < rnum3) ? "true" : "false") << std::endl;

        // Operation <
        std::cout << rnum2 << " > " << rnum3 << " = " << ((rnum2 > rnum3) ? "true" : "false") << std::endl;

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

    auto throw_error = [] (auto& oper, int line) {
        std::stringstream strm;
        strm << "Test case (" << oper << ") failed at line: " << line;
        throw std::runtime_error(strm.str());
    };

    rational_t rnum1 {1,2};
    rational_t rnum2 {2,3};

    if ((rnum1 + rnum2) != rational_t(7,6))
         throw_error("+", __LINE__);

    if ((rnum1 - rnum2) != rational_t(-1,6))
         throw_error("-", __LINE__);

    if ((rnum1 * rnum2) != rational_t(1,3))
         throw_error("*", __LINE__);

    if ((rnum1 / rnum2) != rational_t(3,4))
         throw_error("/", __LINE__);

    if ((rnum1 == rnum2) != false)
         throw_error("==", __LINE__);

    if ((rnum1 < rnum2) != true)
        throw_error("<", __LINE__);

    // infinity
    rnum1 = {1,0};
    rnum2 = {2,0};


    auto res = rnum1 + rnum2;
    if (res.get_num() != 1 && res.get_den() != 0) // inf
        throw_error("+", __LINE__);

    res = rnum1 - rnum2;
    if (res.get_num() != 0 && res.get_den() != 0) // NaN
        throw_error("-", __LINE__);

    res = rnum1 * rnum2;
    if (res.get_num() != 1 && res.get_den() != 0) // inf
        throw_error("*", __LINE__);

    res = rnum1 / rnum2;
    if (res.get_num() != 0 && res.get_den() != 0) // NaN
        throw_error("/", __LINE__);

    res = rnum1 * rational_t{0};
    if (res.get_num() != 0 && res.get_den() != 0) // NaN
        throw_error("*", __LINE__);


    if ((rational_t{1,2} / rnum2) != rational_t(0))
        throw_error("/", __LINE__);

    if ((rnum1 == rnum2) != false) {
        throw_error("==", __LINE__);
    }
    if ((rnum1 > rnum2) != false) {
        throw_error(">", __LINE__);
    }
    if ((rnum1 < rnum2) != false) {
        throw_error("<", __LINE__);
    }
    if ((rnum1 != rnum2) != true) {
        throw_error("!=", __LINE__);
    }


    // NaN
    rnum1 = {0,0};
    rnum2 = rnum1;
    {
    auto res = rnum1 + rnum2;
    if (res.get_num() != 0 && res.get_den() != 0)
        throw_error("+", __LINE__);

    res = rnum1 - rnum2;
    if (res.get_num() != 0 && res.get_den() != 0)
        throw_error("-", __LINE__);

    res = rnum1 * rnum2;
    if (res.get_num() != 0 && res.get_den() != 0)
        throw_error("*", __LINE__);

    res = rnum1 / rnum2;
    if (res.get_num() != 0 && res.get_den() != 0)
        throw_error("/", __LINE__);
    }

    if ((rnum1 == rational_t{2,2}) != false) {
        throw_error("==", __LINE__);
    }
    if ((rnum1 > rational_t{2,2}) != false) {
        throw_error(">", __LINE__);
    }
    if ((rnum1 < rational_t{2,2}) != false) {
        throw_error("<", __LINE__);
    }
    if ((rnum1 != rational_t{2,2}) != true) {
        throw_error("!=", __LINE__);
    }
    if ((rnum1 == rnum2) != false) {
        throw_error("==", __LINE__);
    }
    if ((rnum1 > rnum2) != false) {
        throw_error(">", __LINE__);
    }
    if ((rnum1 < rnum2) != false) {
        throw_error("<", __LINE__);
    }
    if ((rnum1 != rnum2) != true) {
        throw_error("!=", __LINE__);
    }

    // TODO

}

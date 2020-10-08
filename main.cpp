// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// CPP course, task 1
// (c) Oleksiy Svynchuk
//
#include <iostream>
#include <set>
#include <sstream>
#include <chrono>
#include "rational.h"

// NOTE:
// To run unit tests select appropriate project: task1_RationalLib_TEST_osvn
//

using namespace cpp_course;

rational_t calculate_pi () {
    rational_t pi {4};

    for (int n=1; n < 100; ++n) {
        auto num = (n % 2 == 0 ? 4 : -4);
        auto den = (n << 1) + 1;
        rational_t frac {num, den};
        if (pi.get_num() * den + num * pi.get_den() < 0l) break;
        if (pi.get_den() * den < 0l) break;

        pi += frac;
    }
    return pi;
}

int main() {
    std::cout << "Calculating Pi..." << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    auto pi = calculate_pi();
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Pi : " << pi << std::endl;
    std::cout << "Pi : " << static_cast<double>(pi) << std::endl;

    std::cout << "found in " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
    return 0;
}


#if 0
int main() {
    try {
        // Testing console in/out + several basic operations
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

    } catch (std::exception& ex) {
        std::cout << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
#endif

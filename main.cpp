// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <iostream>
#include "rational.h"


int main() {
    try {
        // Input 2 numbers
        rational_t rnum2;
        std::cin >> rnum2;
        std::cout << rnum2 << std::endl;

        rational_t rnum3;
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

    } catch (std::exception& ex) {
        std::cout << "Error: " << ex.what() << std::endl;
        return 1;
    }

    // TBD: impl. some test cases

    return 0;
}

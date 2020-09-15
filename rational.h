#pragma once
#ifndef RATIONAL_T_H
#define RATIONAL_T_H

#include <iostream>

class rational_t {
public:
    rational_t() = default;
    rational_t(int num, int den);
    rational_t& operator += (const rational_t& rhs);
    rational_t& operator -= (const rational_t& rhs);
    rational_t& operator *= (const rational_t& rhs);
    rational_t& operator /= (const rational_t& rhs);
    friend std::ostream& operator << (std::ostream& os, const rational_t& rhs);
    friend std::istream& operator >> (std::istream& os, rational_t& rhs);
private:
    void reduce();
    int m_num =0;
    int m_den =0;
};

rational_t operator + (const rational_t& lhs, const rational_t& rhs);
rational_t operator - (const rational_t& lhs, const rational_t& rhs);
rational_t operator * (const rational_t& lhs, const rational_t& rhs);
rational_t operator / (const rational_t& lhs, const rational_t& rhs);


#endif // RATIONAL_T_H

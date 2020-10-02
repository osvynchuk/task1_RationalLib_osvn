#pragma once
#ifndef RATIONAL_T_H
#define RATIONAL_T_H
//
// CPP course
// (c) Oleksiy Svynchuk
//
#include <iostream>

class rational_t {
public:
    rational_t() = default;
    rational_t(int num, int den = 1);
    rational_t& operator += (const rational_t& rhs);
    rational_t& operator -= (const rational_t& rhs);
    rational_t& operator *= (const rational_t& rhs);
    rational_t& operator /= (const rational_t& rhs);
    bool operator == (const rational_t& rhs) const;
    bool operator != (const rational_t& rhs) const;
    bool operator < (const rational_t& rhs) const;
    bool operator > (const rational_t& rhs) const;
    friend std::ostream& operator << (std::ostream& os, const rational_t& rhs);
    friend std::istream& operator >> (std::istream& is, rational_t& rhs);
    int get_num() { return m_num; };
    int get_den() { return m_den; };

private:
    void reduce();
    bool is_nan() const;
    bool is_inf() const;
    int m_num =0;
    int m_den =0;
};

rational_t operator + (rational_t lhs, const rational_t& rhs);
rational_t operator - (rational_t lhs, const rational_t& rhs);
rational_t operator * (rational_t lhs, const rational_t& rhs);
rational_t operator / (rational_t lhs, const rational_t& rhs);


#endif // RATIONAL_T_H

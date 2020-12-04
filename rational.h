#pragma once
#ifndef RATIONAL_T_H
#define RATIONAL_T_H
//
// CPP course
// (c) Oleksiy Svynchuk
//
#include <iostream>

namespace cpp_course {

class rational_t {
public:
    static const rational_t ZERO;
    static const rational_t INF;
    static const rational_t NaN;

    rational_t() = default;
    rational_t(const rational_t&) = default;
    rational_t& operator = (const rational_t& rhs) = default;
    ~rational_t() = default;
    rational_t(long long num, long long den = 1);
    inline rational_t& operator += (const rational_t& rhs);
    inline rational_t& operator -= (const rational_t& rhs);
    inline rational_t& operator *= (const rational_t& rhs);
    inline rational_t& operator /= (const rational_t& rhs);
    rational_t& operator += (long long rhs);
    rational_t& operator -= (long long rhs);
    rational_t& operator ++ ();
    rational_t& operator -- ();
    rational_t operator ++ (int);
    rational_t operator -- (int);
    bool operator == (const rational_t& rhs) const;
    bool operator != (const rational_t& rhs) const;
    bool operator < (const rational_t& rhs) const;
    bool operator > (const rational_t& rhs) const;
    rational_t operator + () const;
    rational_t operator - () const;
    explicit operator double () const;
    friend std::ostream& operator << (std::ostream& os, const rational_t& rhs);
    friend std::istream& operator >> (std::istream& is, rational_t& rhs);
    long long get_num() const { return m_num; }
    long long get_den() const { return m_den; }
    bool is_nan() const;
    bool is_inf() const;

private:
    static long long gcd (long long a, long long b) {
         if (a==0) return b;
         return gcd(b % a, a);
    }
    void reduce();
    long long m_num =0;
    long long m_den =0;
};

rational_t& rational_t::operator += (const rational_t& rhs) {
    if (is_inf() && rhs.is_inf()) { m_num = 1; m_den = 0; return *this;}
    m_num = m_num * rhs.m_den + rhs.m_num * m_den;
    m_den = m_den * rhs.m_den;
    reduce();
    return *this;
}

rational_t& rational_t::operator -= (const rational_t& rhs) {
    m_num = m_num * rhs.m_den - rhs.m_num * m_den ;
    m_den = m_den * rhs.m_den;
    reduce();
    return *this;
}

rational_t& rational_t::operator *= (const rational_t& rhs) {
    if (is_inf() && rhs.is_inf()) { m_num = 1; m_den = 0; return *this;}
    m_num *= rhs.m_num;
    m_den *= rhs.m_den;
    reduce();
    return *this;
}

rational_t& rational_t::operator /= (const rational_t& rhs) {
    m_num *= rhs.m_den;
    m_den *= rhs.m_num;
    if (m_den < 0) {m_den *= -1; m_num *= -1;}
    reduce();
    return *this;
}

rational_t operator + (rational_t lhs, const rational_t& rhs);
rational_t operator - (rational_t lhs, const rational_t& rhs);
rational_t operator * (rational_t lhs, const rational_t& rhs);
rational_t operator / (rational_t lhs, const rational_t& rhs);

rational_t abs (const rational_t& rhs);
rational_t max(const rational_t& lhs, const rational_t& rhs);
rational_t min(const rational_t& lhs, const rational_t& rhs);
rational_t dim(const rational_t& lhs, const rational_t& rhs);
rational_t ceil(const rational_t& rhs);
rational_t floor(const rational_t& rhs);
rational_t round(const rational_t& rhs);
rational_t modf(const rational_t& rhs, rational_t& i_part);
bool isnan(const rational_t& rhs);
bool isinf(const rational_t& rhs);

}

#endif // RATIONAL_T_H

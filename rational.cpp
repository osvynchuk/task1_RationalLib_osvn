// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// CPP course 2020
// (c) Oleksiy Svynchuk
//
#include <iostream>
#include <cmath>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include "rational.h"

namespace cpp_course {

const rational_t rational_t::ZERO {0};
const rational_t rational_t::INF {1,0};
const rational_t rational_t::NaN {0,0};

rational_t::rational_t(long long num, long long den) : m_num{num}, m_den{den} {
    if (m_den < 0) {
        throw std::invalid_argument("Incorrect format");
    }
    reduce();
}

void rational_t::reduce() {
    auto cd = gcd(m_num, m_den);
    if (cd != 0) {
     m_num /= cd;
     m_den /= cd;
    }
}

rational_t& rational_t::operator += (long long rhs) {
    m_num += rhs * m_den;
    reduce();
    return  *this;
}

rational_t& rational_t::operator -= (long long rhs) {
    m_num -= rhs * m_den;
    reduce();
    return  *this;
}

rational_t& rational_t::operator ++ () {
    *this += 1;
    return *this;
}

rational_t& rational_t::operator -- () {
    *this -= 1;
    return *this;
}

rational_t rational_t::operator ++ (int) {
    rational_t tmp(*this);
    ++*this;
    return tmp;
}

rational_t rational_t::operator -- (int) {
    rational_t tmp(*this);
    --*this;
    return tmp;
}

bool rational_t::operator == (const rational_t& rhs) const {
    if (is_nan() || rhs.is_nan() || is_inf() || rhs.is_inf()) return false;
    return m_num == rhs.m_num && m_den == rhs.m_den;
}

bool rational_t::operator != (const rational_t& rhs) const {
    return !(*this == rhs);
}

bool rational_t::operator < (const rational_t& rhs) const {
    if (is_nan() || is_inf()) return false;
    else if (rhs.is_inf()) return true;
    return static_cast<double>(*this) < static_cast<double>(rhs);
}

bool rational_t::operator > (const rational_t& rhs) const {
    if (is_nan() || rhs.is_nan() || rhs.is_inf()) return false;
    return *this != rhs && !(*this < rhs);
}

rational_t rational_t::operator + () const {
    return *this;
}

rational_t rational_t::operator - () const {
    return {-get_num(), get_den()};
}

rational_t::operator double () const {
    return static_cast<double>(m_num)/m_den;
}

rational_t operator + (rational_t lhs, const rational_t& rhs) {
    return lhs += rhs;
}

rational_t operator - (rational_t lhs, const rational_t& rhs) {
    return lhs -= rhs;
}

rational_t operator * (rational_t lhs, const rational_t& rhs) {
    return lhs *= rhs;
}

rational_t operator / (rational_t lhs, const rational_t& rhs) {
    return lhs /= rhs;
}

std::ostream& operator << (std::ostream& os, const rational_t& rhs) {
    if (rhs.m_num == 0 && !rhs.is_nan())
        os << 0;
    else if (rhs.m_den == 1)
        os << rhs.m_num;
    else
        os << rhs.m_num << "/" << rhs.m_den;
    return os;
}

std::istream& operator >> (std::istream& is, rational_t& rhs) {
    std::string read_str;
    std::vector<std::string> parsed;
    is >> read_str;
    boost::split(parsed, read_str, [](char c) { return c == '/'; });
    if (parsed.size() != 2) throw std::invalid_argument("Incorrect format");

    try {
        rhs.m_num = std::stol(parsed[0]);
        rhs.m_den = std::stol(parsed[1]);
    } catch (...) {
        throw std::invalid_argument("Incorrect format");
    }

    if (rhs.m_den < 0) {
       throw std::invalid_argument("Incorrect format");
    }

    rhs.reduce();
    return is;
}

bool rational_t::is_nan() const {
    if (m_num == 0 && m_den == 0) return true;
    return false;
}

bool rational_t::is_inf() const {
    if (m_num != 0 && m_den == 0) return true;
    return false;
}

rational_t abs(const rational_t& rhs) {
    if (rhs.is_nan()) return rhs;
    rational_t tmp {rhs.get_num() < 0 ? -rhs.get_num() : rhs.get_num(), rhs.get_den()};
    return tmp;
}

rational_t max(const rational_t& lhs, const rational_t& rhs) {
    if (lhs.is_nan() && rhs.is_nan()) return lhs;
    else if (lhs.is_nan() && !rhs.is_nan()) return rhs;
    else if (rhs.is_nan() && !lhs.is_nan()) return lhs;
    return lhs < rhs ? rhs : lhs;
}

rational_t min(const rational_t& lhs, const rational_t& rhs) {
    if (lhs.is_nan() && rhs.is_nan()) return lhs;
    else if (lhs.is_nan() && !rhs.is_nan()) return rhs;
    else if (rhs.is_nan() && !lhs.is_nan()) return lhs;
    return lhs < rhs ? lhs : rhs;
}

rational_t dim(const rational_t& lhs, const rational_t& rhs) {
    if (lhs.is_nan() || rhs.is_nan()) return rational_t{0,0};
    if (lhs > rhs) return lhs - rhs;
    else return rational_t::ZERO;
}

rational_t ceil(const rational_t& rhs) {
    if (rhs.is_inf() || rhs.is_nan() || rhs == rational_t::ZERO) return rhs;
    auto num = rhs.get_num();
    while (num % rhs.get_den()) ++num;
    return {num, rhs.get_den()};
}

rational_t floor(const rational_t& rhs) {
    if (rhs.is_inf() || rhs.is_nan() || rhs == rational_t::ZERO) return rhs;
    auto num = rhs.get_num();
    while (num % rhs.get_den()) --num;
    return {num, rhs.get_den()};
}

rational_t round(const rational_t& rhs) {
    if (rhs.is_inf() || rhs.is_nan() || rhs == rational_t::ZERO) return rhs;
     return {static_cast<int>(std::round(static_cast<double>(rhs))), 1};
}

bool isnan(const rational_t& rhs) {
    return rhs.is_nan();
}

bool isinf(const rational_t& rhs) {
    return rhs.is_inf();
}

rational_t modf(const rational_t& rhs, rational_t& i_part) {
    if (rhs == rational_t::ZERO) {
        i_part = rational_t::ZERO;
        return i_part;
    }
    else if (rhs.is_inf() ) {
        i_part = rational_t::INF;
        return rational_t::ZERO;
    }
    else if (rhs.is_nan() ) {
        i_part = rational_t::NaN;
        return rational_t::NaN;
    }

    i_part = floor(rhs);
    return rhs - i_part;
}

}

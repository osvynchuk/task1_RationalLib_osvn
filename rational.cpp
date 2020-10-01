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


rational_t::rational_t(int num, int den) : m_num{num}, m_den{den} {
    if (m_den < 0) {
        throw std::invalid_argument("Incorrect format");
    }
    reduce();
}

void rational_t::reduce() {
    int min = std::abs(std::min(m_num, m_den));
    while (min > 1) {
        if (m_num % min == 0 && m_den % min == 0) break;
        min--;
    }
    if (min > 1) {
        m_num /= min;
        m_den /= min;
    }

    if (m_num == 0 && m_den != 0) m_den = 1;
}

rational_t& rational_t::operator += (const rational_t& rhs) {
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

bool rational_t::operator == (const rational_t& rhs) const {
    return m_num == rhs.m_num && m_den == rhs.m_den;
}

bool rational_t::operator != (const rational_t& rhs) const {
    return !(*this == rhs);
}

bool rational_t::operator < (const rational_t& rhs) const {
    return (float)m_num/m_den < (float)rhs.m_num/rhs.m_den;
}

bool rational_t::operator > (const rational_t& rhs) const {
    return *this != rhs && !(*this < rhs);
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
    if (rhs.m_num == 0)
        os << 0;
    else if (rhs.m_den == 1)
        os << rhs.m_num;
    else
        os << rhs.m_num << "/" << rhs.m_den;
//    if (rhs.m_num == 0 && rhs.m_den == 0) os << " (NaN)";
//    if (rhs.m_num != 0 && rhs.m_den == 0) os << " (Inf)";
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

// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "gtest/gtest.h"
#include "rational.h"
#include <exception>
#include <sstream>

using namespace cpp_course;

TEST(RationalTest, ReduceTest) {
    EXPECT_EQ(rational_t(2,4), rational_t(1, 2));
    EXPECT_EQ(rational_t(0, 2), rational_t(0, 1));
    EXPECT_EQ(rational_t(10, 35), rational_t(2, 7));
}

TEST(RationalTest, IO_RationalToStreamTest) {

    std::stringstream sstrm;
    rational_t rnum1 {1,2};

    sstrm << rnum1;

    rational_t rnum2;
    sstrm >> rnum2;

    EXPECT_EQ(rnum1, rnum2);

    sstrm.clear();
    sstrm << "1/2";
    sstrm >> rnum2;
    EXPECT_EQ(rnum1, rnum2);

    sstrm.clear();
    sstrm << "1/abc";
    EXPECT_THROW( sstrm >> rnum2, std::invalid_argument);

    sstrm.clear();
    sstrm << "deadbeef";
    EXPECT_THROW( sstrm >> rnum2, std::invalid_argument);
}

TEST(RationalTest, Basic_AddSubMulDiv) {

    const rational_t rnum1 {1,2};
    const rational_t rnum2 {2,3};

    EXPECT_EQ((rnum1 + rnum2), rational_t(7, 6));
    EXPECT_EQ((rnum1 - rnum2), rational_t(-1, 6));
    EXPECT_EQ((rnum1 * rnum2), rational_t(1, 3));
    EXPECT_EQ((rnum1 / rnum2), rational_t(3, 4));

    EXPECT_EQ((rnum1 + rnum2), rational_t(7, 6));
    EXPECT_EQ((rnum1 - rnum2), rational_t(-1, 6));
    EXPECT_EQ((rnum1 * rnum2), rational_t(1, 3));
    EXPECT_EQ((rnum1 / rnum2), rational_t(3, 4));

    rational_t rnum3 {1,2};
    rnum3 += 1;
    EXPECT_EQ(rnum3, rational_t(3, 2));
    rnum3 = {1,2};
    rnum3 -= 1;
    EXPECT_EQ(rnum3, rational_t(-1, 2));

    // unary - op test
    EXPECT_EQ(-rnum1, rational_t(-1, 2));
}

TEST(RationalTest, Basic_AddSubMulDiv2) {

    rational_t rnum1 {-1,2};
    rational_t rnum2 {2,3};

    EXPECT_EQ((rnum1 + rnum2), rational_t(1, 6));
    EXPECT_EQ((rnum1 - rnum2), rational_t(-7, 6));
    EXPECT_EQ((rnum1 * rnum2), rational_t(-1, 3));
    EXPECT_EQ((rnum1 / rnum2), rational_t(-3, 4));
}

TEST(RationalTest, Basic_IncDec) {

    rational_t rnum1 {1,2};
    rational_t rnum2 {2,3};

    EXPECT_EQ(++rnum1, rational_t(3, 2));
    EXPECT_EQ(--rnum1, rational_t(1, 2));
    EXPECT_EQ(--rnum1, rational_t(-1, 2));

    rnum1 = {1,2};
    rnum2 = {2,3};

    EXPECT_EQ(rnum1++, rational_t(1, 2));
    EXPECT_EQ(rnum1, rational_t(3, 2));
    EXPECT_EQ(rnum2--, rational_t(2, 3));
    EXPECT_EQ(rnum2, rational_t(-1, 3));
}

TEST(RationalTest, Basic_Negative) {
    EXPECT_THROW(rational_t(1,-2), std::invalid_argument);
}

TEST(RationalTest, Basic_EqualLessNeGtTest) {

    rational_t rnum1 {1,2};
    rational_t rnum2 {2,3};
    rational_t rnum3 {4,6};
    rational_t rnum4 {-1,2};

    EXPECT_FALSE(rnum1 == rnum2);
    EXPECT_TRUE(rnum2 == rnum3);
    EXPECT_TRUE(rnum1 < rnum2);
    EXPECT_TRUE(rnum4 < rnum1);
    EXPECT_TRUE(rnum1 != rnum2);
    EXPECT_FALSE(rnum2 != rnum3);
    EXPECT_FALSE(rnum1 > rnum2);
    EXPECT_TRUE(rnum2 > rnum1);
}

TEST(RationalTest, InfinityTest) {

    rational_t Inf1 {1,0};
    rational_t Inf2 {2,0};

    EXPECT_TRUE((Inf1 != Inf2));
    EXPECT_FALSE((Inf1 == Inf2));
    EXPECT_FALSE((Inf1 < Inf2));
    EXPECT_FALSE((Inf1 > Inf2));

    auto result = Inf1 + Inf2;  // Inf
    EXPECT_EQ(result.get_num(), 1);
    EXPECT_EQ(result.get_den(), 0);

    result = Inf1 - Inf2;  // NaN
    EXPECT_EQ(result.get_num(), 0);
    EXPECT_EQ(result.get_den(), 0);

    result = Inf1 * Inf2;  // Inf
    EXPECT_EQ(result.get_num(), 1);
    EXPECT_EQ(result.get_den(), 0);

    result = Inf1 / Inf2;  // NaN
    EXPECT_EQ(result.get_num(), 0);
    EXPECT_EQ(result.get_den(), 0);


    result = Inf1 * rational_t {0};  // NaN
    EXPECT_EQ(result.get_num(), 0);
    EXPECT_EQ(result.get_den(), 0);

    result = rational_t{1,2} / Inf1;  // 0
    EXPECT_EQ(result, rational_t {0});

    result = rational_t{1,2} / rational_t {0};  // Inf
    EXPECT_EQ(result.get_num(), 1);
    EXPECT_EQ(result.get_den(), 0);
}

TEST(RationalTest, NaNTest) {

    rational_t NaN1 {0,0};
    rational_t NaN2 {0,0};

    EXPECT_TRUE((NaN1 != NaN2));
    EXPECT_FALSE((NaN1 == NaN2));
    EXPECT_FALSE((NaN1 < NaN2));
    EXPECT_FALSE((NaN1 > NaN2));

    EXPECT_FALSE((NaN1 == rational_t{2,2}));
    EXPECT_FALSE((NaN1 > rational_t{2,2}));
    EXPECT_FALSE((NaN1 < rational_t{2,2}));
    EXPECT_TRUE((NaN1 != rational_t{2,2}));

    auto result = NaN1 + NaN2;  // NaN
    EXPECT_EQ(result.get_num(), 0);
    EXPECT_EQ(result.get_den(), 0);

    result = NaN1 - NaN2;  // NaN
    EXPECT_EQ(result.get_num(), 0);
    EXPECT_EQ(result.get_den(), 0);

    result = NaN1 * NaN2;  // NaN
    EXPECT_EQ(result.get_num(), 0);
    EXPECT_EQ(result.get_den(), 0);

    result = NaN1 / NaN2;  // NaN
    EXPECT_EQ(result.get_num(), 0);
    EXPECT_EQ(result.get_den(), 0);
}

TEST(RationalTest, Extended_MinMaxAbs) {
    rational_t rnum1 {1,2};
    rational_t rnum2 {2,3};
    EXPECT_EQ(min(rnum1, rnum2), rnum1);
    EXPECT_EQ(max(rnum1, rnum2), rnum2);

    EXPECT_EQ(min(rnum1, rational_t::NaN), rnum1);
    EXPECT_EQ(max(rational_t::NaN, rnum2), rnum2);

    auto r = min(rational_t::NaN, rational_t::NaN);
    EXPECT_EQ(r.get_num(), 0);
    EXPECT_EQ(r.get_den(), 0);
    r = max(rational_t::NaN, rational_t::NaN);
    EXPECT_EQ(r.get_num(), 0);
    EXPECT_EQ(r.get_den(), 0);

    EXPECT_EQ(min(rnum1, rational_t::INF), rnum1);

    EXPECT_EQ(abs(rnum2), rational_t(2,3));
    rational_t rnum3 {-2,3};
    EXPECT_EQ(abs(rnum3), rational_t(2,3));
}

TEST(RationalTest, Extended_Ceil) {
    EXPECT_EQ(ceil(rational_t(5,2)), rational_t(3, 1));

    rational_t rnum_0 {0};
    EXPECT_EQ(ceil(rnum_0), rational_t::ZERO);

    rational_t NaN {0,0};
    auto ret = ceil(NaN);

    EXPECT_EQ(ret.get_num(), 0);
    EXPECT_EQ(ret.get_den(), 0);
}

TEST(RationalTest, Extended_Dim) {
    rational_t rnum1 {1,2};
    rational_t rnum2 {2,3};
    EXPECT_EQ(dim(rnum1, rnum2), rational_t(0));
    EXPECT_EQ(dim(rnum2, rnum1), rational_t(1,6));
}

TEST(RationalTest, Extended_Floor) {
    EXPECT_EQ(floor(rational_t(5,2)), rational_t(2, 1));

    rational_t rnum_0 {0};
    EXPECT_EQ(floor(rnum_0), rational_t::ZERO);

    rational_t NaN {0,0};
    auto ret = floor(NaN);

    EXPECT_EQ(ret.get_num(), 0);
    EXPECT_EQ(ret.get_den(), 0);
}

TEST(RationalTest, Extended_Round) {
    EXPECT_EQ(round(rational_t(5,2)), rational_t(3, 1));
    EXPECT_EQ(round(rational_t(1,2)), rational_t(1, 1));
    EXPECT_EQ(round(rational_t(1,3)), rational_t::ZERO);

    rational_t rnum_0 {0};
    EXPECT_EQ(round(rnum_0), rational_t::ZERO);

    rational_t NaN {0,0};
    auto ret = round(NaN);

    EXPECT_EQ(ret.get_num(), 0);
    EXPECT_EQ(ret.get_den(), 0);
}

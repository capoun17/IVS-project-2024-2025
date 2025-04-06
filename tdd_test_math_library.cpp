#include <gtest/gtest.h>
#include "math_library.h"

TEST(MathLibraryTest, AddTest) {
    EXPECT_EQ(add(0, 0), 0);
    EXPECT_EQ(add(2,3), 5);
    EXPECT_EQ(add(-5, 3), 2);
    EXPECT_EQ(add(-15, -21), -36);
    EXPECT_NE(add(15, 16), -1);
    EXPECT_GT(add(2000, 2555), 2888);
    EXPECT_EQ(add(1244863258, 895875569), 2140738827);
    EXPECT_THROW(add(INT_MAX, 1), std::overflow_error);
    EXPECT_THROW(add(INT_MIN, -1), std::overflow_error);
}

TEST(MathLibraryTest, SubstractTest) {
    EXPECT_EQ(substract(0, 0), 0);
    EXPECT_EQ(substract(20, 10), 10);
    EXPECT_EQ(substract(8, 18), -10);
    EXPECT_EQ(substract(-22, -5), -17);
    EXPECT_EQ(substract(1000, 355), 645);
    EXPECT_EQ(substract(-56988, -698547), 641559);
    EXPECT_LT(substract(500, 250), 333);
    EXPECT_EQ(substract(2087624759, 1569325961), 518298798);
    EXPECT_THROW(substract(INT_MIN, 1), std::overflow_error);
    EXPECT_THROW(substract(INT_MAX, -1), std::overflow_error);
}

TEST(MathLibraryTest, MultiplyTest) {
    EXPECT_EQ(multiply(5, 4), 20);
    EXPECT_EQ(multiply(12, 11), 132);
    EXPECT_EQ(multiply(-5, 9), -45);
    EXPECT_EQ(multiply(-7, -4), 28);
    EXPECT_EQ(multiply(2563, 0), 0);
    EXPECT_NE(multiply(698, 0), 698);
    EXPECT_EQ(multiply(0, 0), 0);
    EXPECT_EQ(multiply(465, 7956), 3699540);
    EXPECT_THROW(multiply(INT_MAX, 2), std::overflow_error);
}

TEST(MathLibraryTest, DivideTest) {
    EXPECT_EQ(divide(25, 5), 5);
    EXPECT_EQ(divide(63, 7), 9);
    EXPECT_EQ(divide(-90, 5), -18);
    EXPECT_EQ(divide(-18, -6), 3);
    EXPECT_EQ(divide(0, 20), 0);
    EXPECT_THROW(divide(6, 0), std::invalid_argument);
    EXPECT_THROW(divide(0, 0), std::invalid_argument);
}

TEST(MathLibraryTest, FactorialTest) {
    EXPECT_EQ(factorial(0), 1);
    EXPECT_EQ(factorial(1), 1);
    EXPECT_EQ(factorial(2), 2);
    EXPECT_EQ(factorial(4), 24);
    EXPECT_EQ(factorial(7), 5040);
    EXPECT_GT(factorial(10), 10);
    EXPECT_THROW(factorial(-1), std::invalid_argument);
    EXPECT_THROW(factorial(-55), std::invalid_argument);
    EXPECT_THROW(factorial(25), std::overflow_error);
}

TEST(MathLibraryTest, PowerTest) {
    EXPECT_EQ(power(2, 2), 4);
    EXPECT_EQ(power(2, 4), 16);
    EXPECT_EQ(power(1, 0), 1);
    EXPECT_EQ(power(-56, 0), 1);
    EXPECT_EQ(power(3, 3), 27);
    EXPECT_EQ(power(-5, 2), 25);
    EXPECT_EQ(power(-10, 7), -10000000);
    EXPECT_EQ(power(456, 0), 1);
    EXPECT_NE(power(2, 3), 4);
    EXPECT_THROW(power(4, -1), std::invalid_argument);
    EXPECT_THROW(power(INT_MAX, INT_MAX), std::overflow_error);

}

// root(x,n) = n-th root of x
TEST(MathLibraryTest, RootTest) {
    EXPECT_EQ(root(4, 2), 2);
    EXPECT_EQ(root(16, 2), 4);
    EXPECT_EQ(root(81, 2), 9);
    EXPECT_EQ(root(27, 3), 3);
    EXPECT_EQ(root(-125, 3), -5);
    EXPECT_NE(root(36, 2), 6);
    EXPECT_THROW(root(5, 0), std::invalid_argument);
    EXPECT_THROW(root(-36, 2), std::invalid_argument);
    EXPECT_THROW(root(64, -3), std::invalid_argument);
}
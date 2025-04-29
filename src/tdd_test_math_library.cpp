#include <gtest/gtest.h>
#include "mathlib.h"
#include <climits>

TEST(MathLibraryTest, AddTest) {
    EXPECT_EQ(add(0, 0), 0);
    EXPECT_EQ(add(2,3), 5);
    EXPECT_EQ(add(-5, 3), -2);
    EXPECT_EQ(add(-15, -21), -36);
    EXPECT_NE(add(15, 16), -1);
    EXPECT_GT(add(2000, 2555), 2888);
    EXPECT_EQ(add(1244863258, 895875569), 2140738827);
    EXPECT_THROW(add(DBL_MAX, DBL_MAX), std::overflow_error);
    EXPECT_THROW(add(DBL_MAX, 1e308), std::overflow_error);

    EXPECT_DOUBLE_EQ(add(0.1, 0.2), 0.3);
    EXPECT_DOUBLE_EQ(add(-6.4, 2.8), -3.6);
    EXPECT_DOUBLE_EQ(add(11.001, 22.002), 33.003);
    EXPECT_DOUBLE_EQ(add(0.0000005, 0.0000009), 0.0000014);
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
    EXPECT_THROW(substract(DBL_MAX, -DBL_MAX), std::overflow_error);
    EXPECT_THROW(substract(-DBL_MAX, DBL_MAX), std::overflow_error);

    EXPECT_DOUBLE_EQ(substract(0.9, 0.4), 0.5);
    EXPECT_DOUBLE_EQ(substract(-2.5, -4.9), 2.4);
    EXPECT_DOUBLE_EQ(substract(23.004, 9.003), 14.001);
    EXPECT_DOUBLE_EQ(substract(0.00005, 0.00004), 0.00001);
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
    EXPECT_THROW(multiply(DBL_MAX, 2), std::overflow_error);

    EXPECT_DOUBLE_EQ(multiply(0.4, 0.6), 0.24);
    EXPECT_DOUBLE_EQ(multiply(-3.3, 9.7), -32.01);
    EXPECT_DOUBLE_EQ(multiply(-5.0005, -4.0004), 20.0040002);
    EXPECT_DOUBLE_EQ(multiply(102.012, 58.02), 5918.73624);
    EXPECT_THROW(multiply(DBL_MAX, 1.1), std::overflow_error);
    EXPECT_THROW(multiply(-DBL_MAX, 1.2), std::overflow_error);
}

TEST(MathLibraryTest, DivideTest) {
    EXPECT_EQ(divide(25, 5), 5);
    EXPECT_EQ(divide(63, 7), 9);
    EXPECT_EQ(divide(-90, 5), -18);
    EXPECT_EQ(divide(-18, -6), 3);
    EXPECT_EQ(divide(0, 20), 0);
    EXPECT_THROW(divide(6, 0), std::invalid_argument);
    EXPECT_THROW(divide(0, 0), std::invalid_argument);

    EXPECT_DOUBLE_EQ(divide(0.8, 2), 0.4);
    EXPECT_DOUBLE_EQ(divide(-0.64, 8), -0.08);
    EXPECT_DOUBLE_EQ(divide(100.25, 6.25), 16.04);
    EXPECT_DOUBLE_EQ(divide(-78.4, -12.6), 6.222222222222222);
    EXPECT_THROW(divide(77.9 , 0.0), std::invalid_argument);
    EXPECT_THROW(divide(-205.11 , 0.0), std::invalid_argument);
    EXPECT_THROW(divide(DBL_MAX, 1e-40), std::overflow_error);
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
    EXPECT_EQ(power(2.0, 2.0), 4.0);
    EXPECT_EQ(power(2.0, 4.0), 16.0);
    EXPECT_EQ(power(1.0, 0.0), 1.0);
    EXPECT_EQ(power(-56.0, 0.0), 1.0);
    EXPECT_EQ(power(3.0, 3.0), 27.0);
    EXPECT_EQ(power(-5.0, 2.0), 25.0);
    EXPECT_EQ(power(-10.0, 7.0), -10000000.0);
    EXPECT_EQ(power(456.0, 0.0), 1.0);
    EXPECT_NE(power(2.0, 3.0), 4.0);
    EXPECT_THROW(power(4.0, -1.0), std::invalid_argument);
    EXPECT_THROW(power(DBL_MAX, INT_MAX), std::overflow_error);

    EXPECT_DOUBLE_EQ(power(2.0, 3.0), 8.0);
    EXPECT_DOUBLE_EQ(power(1.5, 4.0), 5.0625);
    EXPECT_DOUBLE_EQ(power(-5.0, 4.0), 625.0);
    EXPECT_DOUBLE_EQ(power(0.5, 3.0), 0.125);
    EXPECT_THROW(power(12.0, -1.0), std::invalid_argument);
    EXPECT_THROW(power(5.0, 2.1), std::invalid_argument);
    EXPECT_THROW(power(DBL_MAX, 3.0), std::overflow_error);
    EXPECT_THROW(power(-DBL_MAX, 2.0), std::overflow_error);
}

// root(x,n) = n-th root of x
TEST(MathLibraryTest, RootTest) {
    EXPECT_NEAR(root(4.0, 2), 2.0, 1e-5);
    EXPECT_NEAR(root(16.0, 2), 4.0, 1e-5);
    EXPECT_NEAR(root(81.0, 2), 9.0, 1e-5);
    EXPECT_NEAR(root(27.0, 3), 3.0, 1e-5);
    EXPECT_NEAR(root(-125.0, 3), -5.0, 1e-5);
    EXPECT_NEAR(root(36.0, 2), 6.0, 1e-5);
    EXPECT_THROW(root(5, 0), std::invalid_argument);
    EXPECT_THROW(root(-36, 2), std::invalid_argument);
    EXPECT_THROW(root(64, -3), std::invalid_argument);
    
    EXPECT_NEAR(root(-27.0, 3), -3.0, 1e-5);
    EXPECT_NEAR(root(81.0, 4), 3.0, 1e-5);
    EXPECT_NEAR(root(32.0, 5), 2.0, 1e-5);
    EXPECT_NEAR(root(243.0, 5), 3.0, 1e-5);
    EXPECT_THROW(root(88.0, -4.5), std::invalid_argument);
    EXPECT_THROW(root(-16.0, 2.0), std::invalid_argument);
}

TEST(MathLibraryTest, GreatestCommonDivisorTest) {
    EXPECT_EQ(greatest_common_divisor(5, 0), 5);
    EXPECT_EQ(greatest_common_divisor(0, 9), 9);
    EXPECT_EQ(greatest_common_divisor(25, 45), 5);
    EXPECT_EQ(greatest_common_divisor(-262, 48), 2);
    EXPECT_EQ(greatest_common_divisor(128, 32), 32);
    EXPECT_EQ(greatest_common_divisor(-90, -16), 2);
    EXPECT_EQ(greatest_common_divisor(-20420, 750), 10);
    EXPECT_THROW(greatest_common_divisor(0, 0), std::invalid_argument);
}
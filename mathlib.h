#ifndef MATHLIB_H
#define MATHLIB_H

#include <stdexcept>
#include <limits>
#include <cmath>

/**
 * @brief Adds 2 integers with overflow check
 * @param a First integer
 * @param b Second integer
 * @return a + b
 * @throws std::overflow_error if the result would overflow
 */
int add(int a, int b);

/**
 * @brief Subtracts 2 integers with overflow check
 * @param a First integer
 * @param b Second integer
 * @return a - b
 * @throws std::overflow_error if the result would overflow
 */
int substract(int a, int b);

/**
 * @brief Multiplies 2 integers with overflow check
 * @param a First integer
 * @param b Second integer
 * @return a * b
 * @throws std::overflow_error if the result would overflow
 */
int multiply(int a, int b);

/**
 * @brief Divides 2 integers with division by zero check
 * @param a First integer
 * @param b Second integer
 * @return a / b
 * @throws std::invalid_argument if b is zero
 */
int divide(int a, int b);

/**
 * @brief Calculates factorial of an integer
 * @param n Integer
 * @return n!
 * @throws std::invalid_argument if n is negative
 * @throws std::overflow_error if the result would overflow
 */
int factorial(int n);

/**
 * @brief Calculates power of a base to an exponent
 * @param x Base
 * @param n Exponent
 * @return x ^ n
 * @throws std::invalid_argument if n is negative
 * @throws std::overflow_error if the result would overflow
 */
int power(int x, int n);

/**
 * @brief Calculates the n-th root of x
 * @param x Root
 * @param n Root degree
 * @return n-th root of x
 * @throws std::invalid_argument if n is non-positive or if x is negative and n is even
 */
int root(int x, int n);

/**
 * @brief Calculates the Greatest Common Divisor of two integers
 * @param a First integer
 * @param b Second integer
 * @return Greatest common divisor a and b
 * @throws std::invalid_argument if both a and b are zero
 */
int greatest_common_divisor(int a, int b);

#endif // MATHLIB_H

/**
 * @brief Header file for mathlib.cpp
 * @author xcapka06
 */

#ifndef MATHLIB_H
#define MATHLIB_H

#include <stdexcept>
#include <limits>
#include <cmath>


/**
 * @brief Rounds a number to 5 decimal places
 * @param value Number to round
 * @return Rounded number
 */
double round_to_1e5(double value);

/**
 * @brief Adds 2 numbers with overflow check
 * @param a First number
 * @param b Second number
 * @return a + b
 * @throws std::overflow_error if the result would overflow
 */
double add(double a, double b);

/**
 * @brief Subtracts 2 numbers with overflow check
 * @param a First number
 * @param b Second number
 * @return a - b
 * @throws std::overflow_error if the result would overflow
 */
double substract(double a, double b);

/**
 * @brief Multiplies 2 numbers with overflow check
 * @param a First number
 * @param b Second number
 * @return a * b
 * @throws std::overflow_error if the result would overflow
 */
double multiply(double a, double b);

/**
 * @brief Divides 2 numbers with division by zero check
 * @param a First number
 * @param b Second number
 * @return a / b
 * @throws std::invalid_argument if b is zero
 */
double divide(double a, double b);

/**
 * @brief Calculates factorial of a number
 * @param n Integer
 * @return n!
 * @throws std::invalid_argument if n is negative
 * @throws std::overflow_error if the result would overflow
 */
double factorial(double n);

/**
 * @brief Calculates power of a base to an exponent
 * @param x Base
 * @param n Exponent
 * @return x ^ n
 * @throws std::invalid_argument if n is negative
 * @throws std::overflow_error if the result would overflow
 */
double power(double x, double n);

/**
 * @brief Calculates the n-th root of x
 * @param x Root
 * @param n Root degree
 * @return n-th root of x
 * @throws std::invalid_argument if n is non-positive or if x is negative and n is even
 */
double root(double x, int n);

/**
 * @brief Calculates the Greatest Common Divisor of two integers
 * @param a First integer
 * @param b Second integer
 * @return Greatest common divisor a and b
 * @throws std::invalid_argument if both a and b are zero
 */
int greatest_common_divisor(int a, int b);

#endif // MATHLIB_H

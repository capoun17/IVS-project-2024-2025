/**
 * @brief Mathematical library implemnting basic operations and overflow checks
 * @author xcapka06
 */

#include "mathlib.h"
#include <limits>
#include <cmath>
#include <stdexcept>

double round_to_1e5(double value) {
    return std::round(value * 1e5) / 1e5;
}

double add(double a, double b) {

    double result = a + b;
    // Check for overflow when adding positive numbers
    if (std::isinf(result)) 
    {
        throw std::overflow_error("Overflow or underflow in addition");
    }
    if (result > std::numeric_limits<double>::max())
    {
        throw std::overflow_error("Overflow in addition");
    }
    // Check for overflow when adding negative numbers
    if (result < std::numeric_limits<double>::lowest())
    {
        throw std::overflow_error("Overflow in addition");
    }

    return result;
}

double substract(double a, double b) {
    // Subtraction can be rewritten as a + (-b)
    // Check for overflow when negating b
    if (b == std::numeric_limits<double>::lowest())
    {
        throw std::overflow_error("Overflow in subtraction");
    }
    double result = add(a, -b);
    return result;
}

double multiply(double a, double b) {
    // Handle special cases
    if (a == 0 || b == 0)
    {
        return 0;
    }
    
    // Check for overflow
    if ((a > 0 && b > 0 && a > std::numeric_limits<double>::max() / b) ||
        (a < 0 && b < 0 && a < std::numeric_limits<double>::max() / b) ||
        (a > 0 && b < 0 && b < std::numeric_limits<double>::lowest() / a) ||
        (a < 0 && b > 0 && a < std::numeric_limits<double>::lowest() / b))
    {
        throw std::overflow_error("Overflow in multiplication");
    }
    
    return a * b;
}

double divide(double a, double b) {
    if (b == 0)
    {
        throw std::invalid_argument("Division by zero");
    }
    
    double result = a / b;
    // Check for overflow
    if (std::isinf(result))
    {
        throw std::overflow_error("Overflow in division");
    }
    
    return result;
}

double factorial(double n) {
    if (std::floor(n) != n)
    {
        throw std::invalid_argument("Non-integer exponent not supported");
    }
    
    if (n < 0)
    {
        throw std::invalid_argument("Factorial not defined for negative numbers");
    }
    
    if (n == 0 || n == 1)
    {
        return 1;
    }
    
    int result = 1;

    for (int i = 2; i <= n; ++i)
    {
        // Check for overflow before multiplying
        if (result > std::numeric_limits<int>::max() / i)
        {
            throw std::overflow_error("Overflow in factorial");
        }
        result *= i;
    }
    
    return result;
}

double power(double x, double n) {
    if (std::isnan(x)) {
        throw std::invalid_argument("Base is NaN");
    }

    if (std::floor(n) != n) {
        throw std::invalid_argument("Non-integer exponent not supported");
    }

    if (n < 0) {
        throw std::invalid_argument("Negative exponent not supported for power");
    }

    if (x == 0.0) {
        if (n == 0) {
            return 1.0; // 0^0 = 1
        }
        return 0.0;
    }

    if (n == 0) {
        return 1.0;
    }

    double result = 1.0;

    // Count result and check for overflow
    for (int i = 0; i < n; ++i) {
        result *= x;
        if (std::isinf(result)) {
            throw std::overflow_error("Overflow in power calculation");
        }
    }

    return round_to_1e5(result);
}

double root(double x, int n) {
    if (n <= 0)
    {
        throw std::invalid_argument("Root degree must be positive");
    }
    
    if (x == 0)
    {
        return 0;
    }
    
    // For even roots, x must be non-negative
    if (n % 2 == 0 && x < 0)
    {
        throw std::invalid_argument("Cannot compute even root of negative number");
    }
    
    // For odd roots of negative numbers, result will be negative
    bool negative = (x < 0);
    double absX = negative ? -x : x;
    
    // Binary search for the root (geeksforgeeks)
    double left = 0;
    double right = absX;
    double result = 0;

    double tolerance = 1e-6;
    
    while (left <= right)
    {
        double mid = left + (right - left) / 2;
        
        // Check if mid^n would overflow
        bool overflow = false;
        double powResult = 1.0;
        
        for (int i = 0; i < n; ++i) {
            powResult *= mid;
        }
        
        if (powResult > absX)
        {
            right = mid - tolerance;
        }
        else if (powResult < absX)
        {
            left = mid + tolerance;
        }
        else
        {
            result = mid;
            break;
        }

        result = mid;
    }
    
    return round_to_1e5(negative && n % 2 == 1 ? -result : result);
}

int greatest_common_divisor(int a, int b) {
    // Greatest common divisor is not defined when both numbers are 0
    if (a == 0 && b == 0)
    {
        throw std::invalid_argument("Greatest common divisor is not defined for both zeros");
    }
    
    // Negative number -> absolute value
    a = (a < 0) ? -a : a;
    b = (b < 0) ? -b : b;
    
    // Basic assertions
    if (a == 0)
    {
        return b;
    }

    if (b == 0)
    {
        return a;
    }
    
    // Euclidean algorithm (geeksforgeeks)
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    
    return a;
}

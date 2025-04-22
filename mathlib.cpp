#include "mathlib.h"
#include <limits>
#include <cmath>
#include <stdexcept>

int add(int a, int b) {
    // Check for overflow when adding positive numbers
    if (b > 0 && a > std::numeric_limits<int>::max() - b)
    {
        throw std::overflow_error("Integer overflow in addition");
    }
    // Check for overflow when adding negative numbers
    if (b < 0 && a < std::numeric_limits<int>::min() - b)
    {
        throw std::overflow_error("Integer overflow in addition");
    }

    return a + b;
}

int substract(int a, int b) {
    // Subtraction can be rewritten as a + (-b)
    // Check for overflow when negating b
    if (b == std::numeric_limits<int>::min())
    {
        throw std::overflow_error("Integer overflow in subtraction");
    }

    return add(a, -b);
}

int multiply(int a, int b) {
    // Handle special cases
    if (a == 0 || b == 0)
    {
        return 0;
    }
    
    // Check for overflow
    if ((a > 0 && b > 0 && a > std::numeric_limits<int>::max() / b) ||
        (a < 0 && b < 0 && a < std::numeric_limits<int>::max() / b) ||
        (a > 0 && b < 0 && b < std::numeric_limits<int>::min() / a) ||
        (a < 0 && b > 0 && a < std::numeric_limits<int>::min() / b))
    {
        throw std::overflow_error("Integer overflow in multiplication");
    }
    
    return a * b;
}

int divide(int a, int b) {
    if (b == 0)
    {
        throw std::invalid_argument("Division by zero");
    }
    
    // Check for overflow in division (only happens with INT_MIN / -1)
    if (a == std::numeric_limits<int>::min() && b == -1)
    {
        throw std::overflow_error("Integer overflow in division");
    }
    
    return a / b;
}

int factorial(int n) {
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
            throw std::overflow_error("Integer overflow in factorial");
        }
        result *= i;
    }
    
    return result;
}

int power(int x, int n) {
    if (n < 0)
    {
        throw std::invalid_argument("Negative exponent not supported for integer power");
    }

    if (n == 0)
    {
        return 1;
    }

    if (x == 0)
    {
        return 0;
    }

    int64_t result = 1; // For correctly handling overflow

    for (int i = 0; i < n; i++)
    {
        result *= x;
        if (result > std::numeric_limits<int>::max() || result < std::numeric_limits<int>::min())
        {
            throw std::overflow_error("Integer overflow in power calculation");
        }
    }

    return static_cast<int>(result); // Cast back to integer
}

int root(int x, int n) {
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
    int absX = negative ? -x : x;
    
    // Binary search for the integer root (geeksforgeeks)
    int left = 0;
    int right = absX;
    int result = 0;
    
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        
        // Check if mid^n would overflow
        bool overflow = false;
        int powResult = 1;
        
        for (int i = 0; i < n && !overflow; ++i)
        {
            if (powResult > std::numeric_limits<int>::max() / mid)
            {
                overflow = true;
            }
            else 
            {
                powResult *= mid;
            }
        }
        
        if (overflow || powResult > absX)
        {
            right = mid - 1;
        }
        else 
        {
            result = mid;
            left = mid + 1;
        }
    }
    
    return negative && n % 2 == 1 ? -result : result;
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

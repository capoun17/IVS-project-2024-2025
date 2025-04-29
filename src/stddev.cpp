#include <iostream>
#include <vector>
#include <limits>
#include "mathlib.h"

/**
 * @brief Counts standard deviation and prints result on STDOUT
 * @author xlepes00
 */

int main() {
    std::vector<double> numbers;
    double num;
    
    //Reads STDIN
    while (std::cin >> num) {
        numbers.push_back(num);
    }

    //Counts numbers
    size_t n = numbers.size();
    if (n < 2) {
        std::cerr << "At least two numbers are required." << std::endl;
        return 1;
    }

    //Counts stddev
    double sum = 0;
    double sumSqr = 0;
    for (double val : numbers) {
        sum = add(sum, val);
        sumSqr = add(sumSqr, power(val,2));
    }
    double avg = divide(sum, static_cast<double>(n));
    double avgSqr = power(avg, 2);
    double diff = substract(sumSqr, multiply(static_cast<double>(n), avgSqr));
    double variance = divide(diff, static_cast<double>(n - 1));
    double stddev = root(variance, 2);

    std::cout << stddev << std::endl;
    return 0;
}



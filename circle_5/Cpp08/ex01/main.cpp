/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:45:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/13 10:50:05 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <cstdlib> // rand, srand
#include <ctime>   // time
#include "Span.hpp"

/**
 * @brief Entry point for testing the Span class.
 *
 * This test program demonstrates:
 * - The basic usage of Span with a small capacity (5 elements).
 * - Exception handling when adding more elements than the capacity allows.
 * - Using the range-based @c addNumber overload with iterators.
 * - Edge cases where spans cannot be computed (empty or single-element Span).
 * - Performance and correctness with a large number of random values (10,000).
 *
 * @return 0 on success, a non-zero value otherwise.
 */

int main() {
    try {
        std::cout << "== BASIC TEST ==" << std::endl;
        Span sp(5);

        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);

        std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span : " << sp.longestSpan() << std::endl;

        // This should throw: Span is full
        try {
            sp.addNumber(42);
        } catch (const std::exception &e) {
            std::cout << "Exception (add extra): " << e.what() << std::endl;
        }

        std::cout << "\n== RANGE ADD TEST ==" << std::endl;
        std::vector<int> values;
        values.push_back(100);
        values.push_back(200);
        values.push_back(300);

        Span sp2(10);
        sp2.addNumber(values.begin(), values.end()); // add range
        sp2.addNumber(50);
        sp2.addNumber(400);

        std::cout << "Shortest span: " << sp2.shortestSpan() << std::endl;
        std::cout << "Longest span : " << sp2.longestSpan() << std::endl;

        std::cout << "\n== EDGE CASE TESTS ==" << std::endl;
        try {
            Span empty(2);
            std::cout << empty.shortestSpan() << std::endl;
        } catch (const std::exception &e) {
            std::cout << "Empty container: " << e.what() << std::endl;
        }

        try {
            Span one(2);
            one.addNumber(10);
            std::cout << one.shortestSpan() << std::endl;
        } catch (const std::exception &e) {
            std::cout << "Only one element: " << e.what() << std::endl;
        }

        std::cout << "\n== LARGE RANDOM TEST (10,000 NUMBERS) ==" << std::endl;
        Span big(10000);
        std::srand(static_cast<unsigned int>(std::time(NULL)));

        for (int i = 0; i < 10000; ++i)
            big.addNumber(std::rand());

        std::cout << "Shortest span: " << big.shortestSpan() << std::endl;
        std::cout << "Longest span : " << big.longestSpan() << std::endl;
    }
    catch (const std::exception &e) {
        std::cout << "Unhandled exception: " << e.what() << std::endl;
    }

    return 0;
}
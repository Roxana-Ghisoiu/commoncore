/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:29:45 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/03 18:11:48 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

/**
 * @brief Test file for Bureaucrat class.
 *
 * This main function demonstrates:
 *  - Successful creation of Bureaucrat objects with valid grades.
 *  - Printing Bureaucrat objects using the overloaded operator<<.
 *  - Incrementing and decrementing grades within valid limits.
 *  - Exceptions thrown when trying to create a Bureaucrat with an
 *    invalid grade (too high or too low).
 *  - Exceptions thrown when incrementing/decrementing causes the
 *    grade to go out of range.
 */

int main() {
    // Valid Bureaucrat
    try {
        Bureaucrat alice("Alice", 2);
        std::cout << alice << std::endl;

        alice.incrementGrade(); // 2 -> 1
        std::cout << alice << std::endl;

        // This should throw (1 -> 0)
        alice.incrementGrade();
    } catch (std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    // Invalid construction (too low)
    try {
        Bureaucrat bob("Bob", 151);
        std::cout << bob << std::endl;
    } catch (std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    // Invalid construction (too high)
    try {
        Bureaucrat carl("Carl", 0);
        std::cout << carl << std::endl;
    } catch (std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    // Decrement test at lower bound
    try {
        Bureaucrat dave("Dave", 150);
        std::cout << dave << std::endl;

        // This should throw (150 -> 151)
        dave.decrementGrade();
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}
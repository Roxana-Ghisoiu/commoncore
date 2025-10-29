/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:48:19 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/02 17:08:12 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Fixed.hpp"

/** @brief Test program for the Fixed class.
 * Demonstrates the Orthodox Canonical Form and additional constructors/conversions:
 * - Default, int, float, and copy constructors
 * - Assignment operator
 * - Conversion to int and float
 * - Overloaded insertion operator <<
 *
 * The output is expected to match the example provided in the subject PDF.
 */

int main(void) {
    Fixed a;
    Fixed const b(10);
    Fixed const c(42.42f);
    Fixed const d(b);

    a = Fixed(1234.4321f);

    std::cout << "a is " << a << std::endl;
    std::cout << "b is " << b << std::endl;
    std::cout << "c is " << c << std::endl;
    std::cout << "d is " << d << std::endl;

    std::cout << "a is " << a.toInt() << " as integer" << std::endl;
    std::cout << "b is " << b.toInt() << " as integer" << std::endl;
    std::cout << "c is " << c.toInt() << " as integer" << std::endl;
    std::cout << "d is " << d.toInt() << " as integer" << std::endl;

    return 0;
}
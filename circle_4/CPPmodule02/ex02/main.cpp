/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:50:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/03 11:37:29 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** @brief Test program for the Fixed class (ex02).
 * This file contains the main function used to verify the
 * Fixed class features: arithmetic, comparison, increment,
 * decrement, and min/max functions.
 */

#include <iostream>
#include "Fixed.hpp"

int main(void) {
    Fixed a;
    Fixed const b(Fixed(5.05f) * Fixed(2));

    std::cout << a << std::endl;
    std::cout << ++a << std::endl;
    std::cout << a << std::endl;
    std::cout << a++ << std::endl;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << Fixed::max(a, b) << std::endl;

    return 0;
}
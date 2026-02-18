/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:50:25 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/07 13:51:57 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>
#include <string>
#include <cstdlib>
#include <cerrno>
#include <climits>
#include <cctype>
#include <cmath>
#include <limits>
#include <iomanip>
/**
 * @class ScalarConverter
 * @brief Non-instantiable utility that prints conversions of a string literal to char, int, float, and double.
 *
 * Accepts common C++ literal forms:
 *  - char: 'a'
 *  - int: 42, -42
 *  - float: 4.2f, -inff, +inff, nanf
 *  - double: 4.2, -inf, +inf, nan
 * Prints "Non displayable" for non-printable char and "impossible" when a conversion cannot be performed.
 */
class ScalarConverter {
private:
    ScalarConverter();
    ScalarConverter(const ScalarConverter &other);
    ScalarConverter &operator=(const ScalarConverter &other);
    ~ScalarConverter();

public:
    static void convert(const std::string &literal);
};

#endif
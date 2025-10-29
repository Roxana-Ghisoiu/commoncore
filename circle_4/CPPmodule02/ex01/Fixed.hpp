/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:55:19 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/02 17:03:55 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>
#include <cmath>

/**
 * @file Fixed.hpp
 * @brief Declaration of the Fixed class implementing a fixed-point number system.
 *
 * The Fixed class stores numbers in fixed-point representation using 8 fractional bits.
 * It provides:
 * - Orthodox Canonical Form (default constructor, copy constructor, copy assignment, destructor)
 * - Constructors from int and float
 * - Conversions back to int and float
 * - Access to the raw fixed-point representation
 * - An overloaded insertion operator (<<) to print values as float
 */
class Fixed {
private:
    int                 _value;
    static const int    _fractionalBits;

public:
    Fixed();
    Fixed(const Fixed& source);
    Fixed& operator=(const Fixed& other);
    ~Fixed();

    Fixed(const int value);
    Fixed(const float value);

    float toFloat(void) const;
    int   toInt(void) const;

    int  getRawBits(void) const;
    void setRawBits(int const raw);
};

std::ostream& operator<<(std::ostream& os, const Fixed& fx);

#endif
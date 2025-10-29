/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:05:24 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/03 11:36:23 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>

/** @brief Declaration of the Fixed class for fixed-point arithmetic.
 * The Fixed class implements a fixed-point number with 8 fractional bits.
 * It provides:
 *  - Conversions between int, float, and fixed-point.
 *  - Comparison operators.
 *  - Arithmetic operators (+, -, *, /).
 *  - Increment and decrement operators (prefix and postfix).
 *  - Static functions to compute min/max of two Fixed values.
 *  - Stream insertion operator for easy printing.
 */

class Fixed {
private:
    int                 _value;
    static const int    _fractionalBits;
public:
    // Canonical form
    Fixed();
    Fixed(const int value);
    Fixed(const float value);
    Fixed(const Fixed& source);
    ~Fixed();

    // Accessors & conversions
    int     getRawBits(void) const;
    void    setRawBits(int const raw);
    float   toFloat(void) const;
    int     toInt(void) const;

    // Assignment
    Fixed&  operator=(const Fixed& other);

    // Comparisons
    bool    operator>(const Fixed& other) const;
    bool    operator<(const Fixed& other) const;
    bool    operator>=(const Fixed& other) const;
    bool    operator<=(const Fixed& other) const;
    bool    operator==(const Fixed& other) const;
    bool    operator!=(const Fixed& other) const;

    // Arithmetic 
    Fixed   operator+(const Fixed& other) const;
    Fixed   operator-(const Fixed& other) const;
    Fixed   operator*(const Fixed& other) const;
    Fixed   operator/(const Fixed& other) const;

    // ++ / --
    Fixed&  operator++();    // prefix
    Fixed&  operator--();
    Fixed   operator++(int); // postfix
    Fixed   operator--(int);

    // min / max
    static Fixed&          min(Fixed& a, Fixed& b);
    static Fixed&          max(Fixed& a, Fixed& b);
    static const Fixed&    min(const Fixed& a, const Fixed& b);
    static const Fixed&    max(const Fixed& a, const Fixed& b);
};

std::ostream& operator<<(std::ostream& out, const Fixed& fixed);

#endif
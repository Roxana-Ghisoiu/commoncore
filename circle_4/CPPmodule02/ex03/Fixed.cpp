/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:10:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/03 12:48:29 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <cmath>

/** @brief Implementation of the Fixed class.
 * This file defines all member functions and operator overloads
 * declared in Fixed.hpp:
 *  - Constructors, destructor, assignment.
 *  - Conversion functions to int/float.
 *  - Comparison and arithmetic operators.
 *  - Increment/decrement operators.
 *  - Min/max utility functions.
 *  - Stream output operator.
 */

const int Fixed::_fractionalBits = 8;

/* Canonical */
Fixed::Fixed() : _value(0) {}

Fixed::Fixed(const int value) {
    _value = value << _fractionalBits;
}

Fixed::Fixed(const float value) {
    _value = static_cast<int>(roundf(value * (1 << _fractionalBits)));
}

Fixed::Fixed(const Fixed& other) : _value(other._value) {}

Fixed::~Fixed() {}

Fixed& Fixed::operator=(const Fixed& other) {
    if (this != &other)
        _value = other._value;
    return *this;
}

/* Accessors */
int Fixed::getRawBits(void) const { return _value; }

void Fixed::setRawBits(int const raw) { _value = raw; }

float Fixed::toFloat(void) const {
    return static_cast<float>(_value) / static_cast<float>(1 << _fractionalBits);
}

int Fixed::toInt(void) const {
    return _value >> _fractionalBits;
}

/* Comparisons */
bool Fixed::operator>(const Fixed& other) const { return _value > other._value; }
bool Fixed::operator<(const Fixed& other) const { return _value < other._value; }
bool Fixed::operator>=(const Fixed& other) const { return _value >= other._value; }
bool Fixed::operator<=(const Fixed& other) const { return _value <= other._value; }
bool Fixed::operator==(const Fixed& other) const { return _value == other._value; }
bool Fixed::operator!=(const Fixed& other) const { return _value != other._value; }

/* Arithmetic */
Fixed Fixed::operator+(const Fixed& other) const {
    Fixed r;
    r._value = this->_value + other._value;
    return r;
}

Fixed Fixed::operator-(const Fixed& other) const {
    Fixed r;
    r._value = this->_value - other._value;
    return r;
}

Fixed Fixed::operator*(const Fixed& other) const {
    // (a * b) in fixed: (valA * valB) >> fractionalBits
    long long prod = static_cast<long long>(this->_value) * static_cast<long long>(other._value);
    Fixed r;
    r._value = static_cast<int>(prod >> _fractionalBits);
    return r;
}

Fixed Fixed::operator/(const Fixed& other) const {
    Fixed r;
    if (other._value == 0) {
        std::cerr << "Error: division by zero\n";
        r._value = 0;
        return r;
    }
    // (a / b) in fixed: (valA << fractionalBits) / valB
    long long num = (static_cast<long long>(this->_value) << _fractionalBits);
    r._value = static_cast<int>(num / other._value);
    return r;
}

/* ++ / -- */
Fixed& Fixed::operator++() {            // prefix
    ++_value;                           // + epsilon (1 LSB)
    return *this;
}

Fixed& Fixed::operator--() {            // prefix
    --_value;
    return *this;
}

Fixed Fixed::operator++(int) {          // postfix
    Fixed tmp(*this);
    ++(*this);
    return tmp;
}

Fixed Fixed::operator--(int) {          // postfix
    Fixed tmp(*this);
    --(*this);
    return tmp;
}

/* min / max */
Fixed& Fixed::min(Fixed& a, Fixed& b) {
    return (a < b) ? a : b;
}

Fixed& Fixed::max(Fixed& a, Fixed& b) {
    return (a > b) ? a : b;
}

const Fixed& Fixed::min(const Fixed& a, const Fixed& b) {
    return (a < b) ? a : b;
}

const Fixed& Fixed::max(const Fixed& a, const Fixed& b) {
    return (a > b) ? a : b;
}

/* stream output */
std::ostream& operator<<(std::ostream& out, const Fixed& fixed) {
    out << fixed.toFloat();
    return out;
}
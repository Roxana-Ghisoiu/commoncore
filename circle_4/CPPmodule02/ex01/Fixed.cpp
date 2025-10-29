/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:05:15 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/02 17:07:27 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <iostream>


const int Fixed::_fractionalBits = 8;

/**@brief Implementation of the Fixed class defined in Fixed.hpp.
 *
 * This file provides the logic for:
 * - Constructors and destructor
 * - Copy and assignment operators
 * - Conversions between fixed-point, int, and float
 * - Raw bit access
 * - Stream insertion operator for printing
 */

Fixed::Fixed() : _value(0) {
    std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed& source) : _value(source._value) {
    std::cout << "Copy constructor called" << std::endl;
}

Fixed& Fixed::operator=(const Fixed& other) {
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &other)
        this->_value = other._value;
    return *this;
}

Fixed::~Fixed() {
    std::cout << "Destructor called" << std::endl;
}


Fixed::Fixed(const int value) {
    std::cout << "Int constructor called" << std::endl;
    _value = value << _fractionalBits; // value * 2^8
}

Fixed::Fixed(const float value) {
    std::cout << "Float constructor called" << std::endl;
    _value = static_cast<int>(roundf(value * (1 << _fractionalBits)));
}

float Fixed::toFloat(void) const {
    return static_cast<float>(_value) / static_cast<float>(1 << _fractionalBits);
}

int Fixed::toInt(void) const {
    return _value >> _fractionalBits; // _value / 2^8 trunchiat
}


int Fixed::getRawBits(void) const {
    std::cout << "getRawBits member function called" << std::endl;
    return _value;
}

void Fixed::setRawBits(int const raw) {
    _value = raw;
}

std::ostream& operator<<(std::ostream& os, const Fixed& fx) {
    os << fx.toFloat();
    return os;
}


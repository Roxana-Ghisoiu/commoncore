/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:30:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/03 12:46:53 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file Point.cpp
 * @brief Implementation of the Point class.
 */

#include "Point.hpp"
#include <cmath>

Point::Point() : _x(0.0f), _y(0.0f) {}

Point::Point(const float a, const float b) : _x(a), _y(b) {}

Point::Point(const Point& source) : _x(source._x), _y(source._y) {}

Point& Point::operator=(const Point& other) {
    (void)other; // members are const; assignment is a no-op
    return *this;
}

Point::~Point() {}

const Fixed& Point::get_x(void) const { return _x; }
const Fixed& Point::get_y(void) const { return _y; }
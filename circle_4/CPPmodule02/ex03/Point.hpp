/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 12:17:23 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/03 12:38:13 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
# define POINT_HPP
#include "Fixed.hpp"

/* @brief Declaration of a 2D immutable point (x,y) using Fixed coordinates.
 *
 * Point stores two constant Fixed values (_x, _y). Copy assignment exists to
 * satisfy the Orthodox Canonical Form, but cannot modify members (no-op).
 * Use getters to access coordinates. See bsp.cpp for the point-in-triangle test.
 */

class Point {
    private:
        const Fixed _x;
        const Fixed _y;
    
    public:
        Point();
        Point (const float a, const float b);
        Point(const Point& source);
        Point& operator = (const Point& other);
        ~Point();

        /*getter*/
        const Fixed& get_x(void) const;
        const Fixed& get_y(void) const;

};

// Point-in-triangle predicate (strictly inside; edges/vertices return false)
bool bsp( Point const a, Point const b, Point const c, Point const point);

#endif

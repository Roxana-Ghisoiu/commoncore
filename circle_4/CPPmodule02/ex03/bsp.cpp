/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:30:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/03 12:46:38 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file bsp.cpp
 * @brief Implements the barycentric/area-sign test to check if a point is strictly
 *        inside a triangle (returns false on edges or vertices).
 */

#include "Point.hpp"
#include <cmath>

// 2D cross product (z-component) of vectors AB and AP
static Fixed cross(const Point& A, const Point& B, const Point& P) {
    Fixed abx = B.get_x() - A.get_x();
    Fixed aby = B.get_y() - A.get_y();
    Fixed apx = P.get_x() - A.get_x();
    Fixed apy = P.get_y() - A.get_y();
    return (abx * apy) - (aby * apx);
}

bool bsp(Point const a, Point const b, Point const c, Point const p) {
    // Compute oriented areas (signs) relative to each edge
    Fixed c1 = cross(a, b, p);
    Fixed c2 = cross(b, c, p);
    Fixed c3 = cross(c, a, p);

    // On an edge or vertex -> return false (strictly inside only)
    if (c1 == Fixed(0) || c2 == Fixed(0) || c3 == Fixed(0))
        return false;

    // All with the same sign -> inside
    bool hasNeg = (c1 < Fixed(0)) || (c2 < Fixed(0)) || (c3 < Fixed(0));
    bool hasPos = (c1 > Fixed(0)) || (c2 > Fixed(0)) || (c3 > Fixed(0));
    return !(hasNeg && hasPos);
}
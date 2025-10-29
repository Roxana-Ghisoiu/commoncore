/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:10:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/03 12:43:48 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file main.cpp
 * @brief Simple tests for bsp(Point) — strictly inside triangle check.
 *
 * Triangle used in tests:
 *   A(0,0), B(10,0), C(0,10)
 *
 * Expected:
 *  - Inside point      -> true
 *  - Outside point     -> false
 *  - On edge / vertex  -> false
 */

#include <iostream>
#include "Point.hpp"

static void testCase(const char* label, const Point& p, const Point& a, const Point& b, const Point& c, bool expected) {
    bool res = bsp(a, b, c, p);
    std::cout << label << " : " << (res ? "true" : "false")
              << " (expected " << (expected ? "true" : "false") << ")\n";
}

int main() {
    // Triangle vertices
    Point A(0.0f, 0.0f);
    Point B(10.0f, 0.0f);
    Point C(0.0f, 10.0f);

    // Points to test
    Point P_inside(3.0f, 3.0f);      // strictly inside
    Point P_out1(10.0f, 10.0f);      // outside
    Point P_out2(-1.0f, 2.0f);       // outside
    Point P_edge(5.0f, 5.0f);        // on edge AC (should be false)
    Point P_edge2(5.0f, 0.0f);       // on edge AB (should be false)
    Point P_vertexA(0.0f, 0.0f);     // exactly at A (should be false)

    std::cout << "Triangle: A(0,0)  B(10,0)  C(0,10)\n";
    testCase("Inside",  P_inside,  A, B, C, true);
    testCase("Outside", P_out1,    A, B, C, false);
    testCase("Outside", P_out2,    A, B, C, false);
    testCase("OnEdge",  P_edge,    A, B, C, false);
    testCase("OnEdge",  P_edge2,   A, B, C, false);
    testCase("VertexA", P_vertexA, A, B, C, false);

    return 0;
}
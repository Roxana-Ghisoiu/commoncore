/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:25:16 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/09 11:39:23 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>
#include "Fixed.hpp"  
#include "Point.hpp" 

// Declarația funcției bsp
bool bsp(Point const a, Point const b, Point const c, Point const point);

// Helper mic pentru afișare
static void runCase(const char* label,
                    const Point& A, const Point& B, const Point& C,
                    const Point& P, bool expected)
{
    bool inside = bsp(A, B, C, P);
    std::cout << std::left << std::setw(12) << label
              << ": " << std::boolalpha << inside
              << " (expected " << (expected ? "true" : "false") << ")\n";
}

int main() {
    // Triunghi de referință
    Point A(0.0f, 0.0f);
    Point B(10.0f, 0.0f);
    Point C(0.0f, 10.0f);

    std::cout << "Triangle: A(0,0)  B(10,0)  C(0,10)\n";

    // Cazuri de bază – clare și ușor de urmărit
    runCase("Inside",   A, B, C, Point(2.0f, 2.0f),  true);
    runCase("Outside",  A, B, C, Point(11.0f, 0.0f), false);
    runCase("Outside2", A, B, C, Point(-1.0f, 5.0f), false);
    runCase("OnEdgeAB", A, B, C, Point(5.0f, 0.0f),  false);
    runCase("OnEdgeAC", A, B, C, Point(0.0f, 5.0f),  false);
    runCase("VertexA",  A, B, C, Point(0.0f, 0.0f),  false);

    // Opțional: un test „aproape de muchie” (pasul minim la 8 frac bits e 1/256)
    const float eps = 1.0f / 256.0f;
    runCase("NearAB_in",  A, B, C, Point(5.0f,  eps),  true);
    runCase("NearAB_out", A, B, C, Point(5.0f, -eps),  false);

    // Opțional: verificare că ordinea vârfurilor nu contează
    runCase("Perm_BCA",  B, C, A, Point(2.0f, 2.0f),  true);
    runCase("Perm_CAB",  C, A, B, Point(2.0f, 2.0f),  true);

        // Degenerate triangle (all three points collinear)
    Point D1(0.0f, 0.0f);
    Point D2(5.0f, 0.0f);
    Point D3(10.0f, 0.0f);

    std::cout << "\nDegenerate triangle: A(0,0)  B(5,0)  C(10,0)\n";
    runCase("Deg_onLine",  D1, D2, D3, Point(2.0f, 0.0f), false);
    runCase("Deg_offLine", D1, D2, D3, Point(2.0f, 1.0f), false);


    return 0;
}

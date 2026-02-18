/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:38:08 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/07 13:53:18 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

/**
 * @brief Entry point: expects a single argument (C++ scalar literal) and prints conversions.
 *
 * Usage:
 *   ./convert <literal>
 * Returns non-zero on wrong usage.
 */
int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <literal>" << std::endl;
        return 1;
    }
    ScalarConverter::convert(std::string(argv[1]));
    return 0;
}
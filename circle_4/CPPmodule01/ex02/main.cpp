/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:09:40 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/01 17:28:45 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

/**
 * @brief Entry point of the HI THIS IS BRAIN program.
 *
 * This program demonstrates the relationship between:
 * - a string variable,
 * - a pointer to that string (stringPTR),
 * - and a reference to that string (stringREF).
 *
 * It prints both the memory addresses and the values, showing that
 * the pointer and the reference both point to the same string object.
 *
 * @return int Exit status code (0 on success).
 */
int main(void)
{
    std::string  str = "HI THIS IS BRAIN";
    std::string* stringPTR = &str;
    std::string& stringREF = str;

    // Addresses
    std::cout << "Address of string variable: " << &str << std::endl;
    std::cout << "Address held by stringPTR: "  << stringPTR << std::endl;
    std::cout << "Address held by stringREF: "  << &stringREF << std::endl;

    // Values
    std::cout << "Value of string variable: "   << str << std::endl;
    std::cout << "Value pointed by stringPTR: " << *stringPTR << std::endl;
    std::cout << "Value pointed by stringREF: " << stringREF << std::endl;

    return 0;
}

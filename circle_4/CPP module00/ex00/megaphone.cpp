/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:40:22 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/08/28 17:48:24 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <cctype>

/**
 * @brief Convert all characters in a string to uppercase.
 *
 * This function takes a copy of the input string and replaces each character
 * with its uppercase equivalent using std::toupper. Characters that are not
 * alphabetic remain unchanged.
 *
 * @param s The input string to be transformed.
 * @return A new string where all alphabetic characters are uppercase.
 */
std::string messageCapitalize(std::string s) {
    for (size_t i = 0; i < s.length(); i++) {
        s[i] = std::toupper(s[i]);
    }
    return s;
}

/**
 * @brief Entry point of the program.
 *
 * The program simulates a "megaphone" by printing all command-line arguments
 * in uppercase. If no arguments are provided, it prints a default loud noise
 * message.
 *
 * @param argc The number of arguments passed to the program (including the program name).
 * @param argv The array of arguments as C-style strings.
 * @return int Returns 0 on successful execution.
 */
int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *\n";
        return 0;
    }
    for (int i = 1; i < argc; i++) {
        std::cout << messageCapitalize(argv[i]);
    }
    std::cout << "\n";
    return 0;
}

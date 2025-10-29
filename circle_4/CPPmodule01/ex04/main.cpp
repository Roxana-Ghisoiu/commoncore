/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:16:49 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/02 13:20:24 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sed.hpp"

/** @brief Entry point of the program that replaces all occurrences of s1 with s2 in a file.
 *
 * The program takes three parameters:
 * 1. Input filename
 * 2. String to search (s1)
 * 3. String to replace with (s2)
 *
 * It reads the entire content of the input file, replaces every occurrence of s1 with s2,
 * and writes the result into a new file named <filename>.replace.
 * Errors such as wrong arguments, empty strings, or file open failures are handled properly.
 */
int main(int argc, char** argv)
{
    if (argc != 4) {
        std::cerr << "Usage: " << (argc > 0 ? argv[0] : "replace")
                  << " <filename> <s1> <s2>\n";
        return 1;
    }
    const std::string filename = argv[1];
    const std::string s1 = argv[2];
    const std::string s2 = argv[3];

    if (filename.empty()) {
        std::cerr << "Error: filename is empty.\n";
        return 1;
    }
    if (s1.empty()) {
        std::cerr << "Error: s1 must not be empty.\n";
        return 1;
    }

    std::ifstream in(filename.c_str(), std::ios::in);
    if (!in.is_open()) {
        std::cerr << "Error: failed to open input file: " << filename << "\n";
        return 1;
    }

    std::string content((std::istreambuf_iterator<char>(in)),
                         std::istreambuf_iterator<char>());

    const std::string replaced = sed_replace(content, s1, s2);

    std::ofstream out((filename + ".replace").c_str(), std::ios::out);
    if (!out.is_open()) {
        std::cerr << "Error: failed to create output file: "
                  << filename << ".replace\n";
        return 1;
    }

    out << replaced;
    if (!out) {
        std::cerr << "Error: failed to write output file.\n";
        return 1;
    }
    return 0;
}
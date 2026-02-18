/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:32:56 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/13 13:34:34 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>

/**
 * @file main.cpp
 * @brief Entry point for the btc program 
 * that evaluates bitcoin values from an input file.
 */

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    std::ifstream infile(av[1]);
    if (!infile.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    try
    {
        BitcoinExchange btc;
        btc.handleFile(infile);
        infile.close();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}

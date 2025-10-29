/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:25:12 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/08 17:50:03 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

/**
 * @file main.cpp
 * @brief Test program for the Harl class.
 *
 * This file creates a Harl instance and calls the complain method with
 * various levels: DEBUG, INFO, WARNING, ERROR, and an invalid level.
 * It demonstrates that the pointer-to-member function mechanism correctly
 * selects the appropriate message.
 */

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage: ./harl_complain <LEVEL>" << std::endl;
        return 1;
    }
    Harl h;
    h.complain(argv[1]);
    return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:45:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/02 14:48:25 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"
#include <iostream>

/**
 * @file Harl.cpp
 * @brief Implements Harl filtering: prints messages from selected level and above.
 */

Harl::Harl() {}
Harl::~Harl() {}

void Harl::debug() {
    std::cout
        << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. "
        << "I really do!" << std::endl;
}

void Harl::info() {
    std::cout
        << "I cannot believe adding extra bacon costs more money. "
        << "You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!"
        << std::endl;
}

void Harl::warning() {
    std::cout
        << "I think I deserve to have some extra bacon for free. "
        << "I’ve been coming for years, whereas you started working here just last month."
        << std::endl;
}

void Harl::error() {
    std::cout << "This is unacceptable! I want to speak to the manager now." << std::endl;
}

static int level_index(const std::string& level) {
    const std::string levels[4] = { "DEBUG", "INFO", "WARNING", "ERROR" };
    for (int i = 0; i < 4; ++i)
        if (level == levels[i]) return i;
    return -1;
}

void Harl::filter(const std::string& level) {
    switch (level_index(level)) {
        case 0:
            std::cout << "[ DEBUG ]" << std::endl;
            debug();
            std::cout << std::endl;
            /* fall through */
        case 1:
            std::cout << "[ INFO ]" << std::endl;
            info();
            std::cout << std::endl;
            /* fall through */
        case 2:
            std::cout << "[ WARNING ]" << std::endl;
            warning();
            std::cout << std::endl;
            /* fall through */
        case 3:
            std::cout << "[ ERROR ]" << std::endl;
            error();
            break;
        default:
            std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
    }
}
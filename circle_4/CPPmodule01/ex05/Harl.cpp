/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:08:18 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/08 17:34:22 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

/**
 * @file Harl.cpp
 * @brief Implements the Harl class methods for different complaint levels.
 *
 * Each private method prints a predefined message for one of the levels:
 * DEBUG, INFO, WARNING, and ERROR. The complain() method uses a lookup
 * mechanism with an array of pointers to member functions, avoiding
 * a long chain of conditional statements.
 */
#include "Harl.hpp"

Harl::Harl() {}
Harl::~Harl() {}

void Harl::debug(void) {
    std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!" << std::endl;
}
void Harl::info(void) {
    std::cout << "I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!" << std::endl;
}
void Harl::warning(void) {
    std::cout << "I think I deserve to have some extra bacon for free. I’ve been coming for years, whereas you started working here just last month." << std::endl;
}
void Harl::error(void) {
    std::cout << "This is unacceptable! I want to speak to the manager now." << std::endl;
}

void Harl::complain(const std::string& level) {
    const std::string levels[4] = {"DEBUG","INFO","WARNING","ERROR"};
    void (Harl::*funcs[4])() = { &Harl::debug, &Harl::info, &Harl::warning, &Harl::error };

    for (int i = 0; i < 4; ++i) {
        if (level == levels[i]) {
            (this->*funcs[i])();   // DOAR un singur mesaj
            return;
        }
    }
    std::cout << "[ Probably complaining about insignificant problems ]" << std::endl;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:05:46 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/01 16:57:44 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

/**
 * @file Zombie.cpp
 * @brief Implements the Zombie class.
 *
 * This file contains the implementation of the Zombie class:
 * - Constructors (default and with name).
 * - Destructor, which prints a message when a Zombie is destroyed.
 * - setName(), used to assign a name to Zombies in a horde.
 * - announce(), which makes the Zombie print its signature message.
 */
Zombie::Zombie() {}

Zombie::Zombie(const std::string& name) : _name(name) {
    std::cout << "Zombie " << _name << " is created" << std::endl;
}

Zombie::~Zombie() {
    std::cout << "Zombie: " << _name << " is destroyed" << std::endl;
}

void Zombie::setName(const std::string& name) {
    _name = name;
    std::cout << "Zombie " << _name << " is created" << std::endl;
}

void Zombie::announce(void) const {
    std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

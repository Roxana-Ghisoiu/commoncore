/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:27:48 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/01 14:27:03 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

/**
 * @brief Constructs a Zombie with the given name.
 *        Prints a creation message for debugging.
 * @param name The name of the Zombie.
 */
Zombie::Zombie(const std::string& name) : _name(name)
{
    std::cout << "Zombie: " << _name << " is created" << std::endl;
}

/**
 * @brief Destructor of the Zombie.
 *        Prints a destruction message for debugging.
 */
Zombie::~Zombie()
{
    std::cout << "Zombie: " << _name << " is destroyed" << std::endl;
}

/**
 * @brief Makes the Zombie announce itself with
 *        the message "<name>: BraiiiiiiinnnzzzZ...".
 */
void Zombie::announce(void) const
{
    std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

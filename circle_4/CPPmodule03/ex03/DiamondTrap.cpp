/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:50:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/04 12:24:57 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"
#include <iostream>

/**
 * @brief Default constructor for DiamondTrap.
 */
DiamondTrap::DiamondTrap()
: ClapTrap("Default_Diamond_clap_name"),
  ScavTrap("Default_Diamond"),
  FragTrap("Default_Diamond"),
  _name("Default_Diamond")
{
    ClapTrap::_hitPoints    = 100; // from FragTrap
    ClapTrap::_energyPoints = 50;  // from ScavTrap
    ClapTrap::_attackDamage = 30;  // from FragTrap
    std::cout << "DiamondTrap default-constructed: " << _name << std::endl;
}

/**
 * @brief Parameterized constructor for DiamondTrap.
 * @param name The DiamondTrap's own name.
 */
DiamondTrap::DiamondTrap(const std::string& name)
: ClapTrap(name + "_clap_name"),
  ScavTrap(name),
  FragTrap(name),
  _name(name)
{
    ClapTrap::_hitPoints    = 100;
    ClapTrap::_energyPoints = 50;
    ClapTrap::_attackDamage = 30;
    std::cout << "DiamondTrap constructed with name: " << _name << std::endl;
}

/**
 * @brief Copy constructor for DiamondTrap.
 * @param other The instance to copy.
 */
DiamondTrap::DiamondTrap(const DiamondTrap& other)
: ClapTrap(other),
  ScavTrap(other),
  FragTrap(other),
  _name(other._name)
{
    std::cout << "DiamondTrap copy-constructed from: " << other._name << std::endl;
}

/**
 * @brief Copy assignment operator for DiamondTrap.
 * @param other The instance to assign from.
 * @return Reference to the assigned object.
 */
DiamondTrap& DiamondTrap::operator=(const DiamondTrap& other)
{
    if (this != &other) {
        ClapTrap::operator=(other);  // single virtual base
        _name = other._name;
    }
    std::cout << "DiamondTrap assigned from: " << other._name << std::endl;
    return *this;
}

/**
 * @brief Destructor for DiamondTrap.
 */
DiamondTrap::~DiamondTrap()
{
    std::cout << "DiamondTrap destroyed: " << _name << std::endl;
}

/**
 * @brief Attack function for DiamondTrap.
 * Delegates to ScavTrap's attack implementation.
 * @param target The target to attack.
 */
void DiamondTrap::attack(const std::string& target)
{
    ScavTrap::attack(target);
}

/**
 * @brief Prints both DiamondTrap's own name and ClapTrap's name.
 */
void DiamondTrap::whoAmI()
{
    std::cout << "DiamondTrap name: " << _name
              << " | ClapTrap name: " << ClapTrap::_name << std::endl;
}

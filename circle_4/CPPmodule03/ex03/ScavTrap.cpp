/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:40:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/04 12:02:05 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** @brief Implementation of the ScavTrap class (CPP03/ex01).
 *
 * ScavTrap is derived from ClapTrap. It has different default stats:
 *  - Hit points: 100
 *  - Energy points: 50
 *  - Attack damage: 20
 *
 * Constructors, destructor, and attack() display distinct messages
 * to differentiate from ClapTrap.
 *
 * Additional ability:
 *  - guardGate(): prints that ScavTrap is now in Gate Keeper mode.
 *
 * Proper inheritance chaining is shown in construction and destruction:
 * ClapTrap is constructed first, followed by ScavTrap. Destruction occurs
 * in reverse order.*/

#include "ScavTrap.hpp"
#include <iostream>

/* Constructors / Destructor */

ScavTrap::ScavTrap() : ClapTrap("default") {
    _hitPoints = 100;
    _energyPoints = 50;
    _attackDamage = 20;
    std::cout << "ScavTrap default-constructed: " << _name << std::endl;
}

ScavTrap::ScavTrap(const std::string& name) : ClapTrap(name) {
    _hitPoints = 100;
    _energyPoints = 50;
    _attackDamage = 20;
    std::cout << "ScavTrap constructed with name: " << _name << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& other) : ClapTrap(other) {
    *this = other;
    std::cout << "ScavTrap copy-constructed from: " << other._name << std::endl;
}

ScavTrap& ScavTrap::operator=(const ScavTrap& other) {
    if (this != &other) {
        ClapTrap::operator=(other);
    }
    std::cout << "ScavTrap assigned from: " << other._name << std::endl;
    return *this;
}

ScavTrap::~ScavTrap() {
    std::cout << "ScavTrap destroyed: " << _name << std::endl;
}

/* Actions */

void ScavTrap::attack(const std::string& target) {
    if (_hitPoints <= 0) {
        std::cout << "ScavTrap " << _name << " cannot attack: no hit points left.\n";
        return;
    }
    if (_energyPoints <= 0) {
        std::cout << "ScavTrap " << _name << " cannot attack: no energy left.\n";
        return;
    }
    _energyPoints -= 1;
    std::cout << "ScavTrap " << _name
              << " ferociously attacks " << target
              << ", dealing " << _attackDamage
              << " points of damage! (EN left: " << _energyPoints << ")\n";
}

void ScavTrap::guardGate() {
    std::cout << "ScavTrap " << _name << " has entered Gate Keeper mode.\n";
}
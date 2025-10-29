/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:05:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/04 12:01:47 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** @brief Implementation of the FragTrap class (CPP03/ex02).
 *
 * FragTrap is derived from ClapTrap. It has different default stats:
 *  - Hit points: 100
 *  - Energy points: 100
 *  - Attack damage: 30
 *
 * Constructors, destructor, and attack() display distinct messages
 * to differentiate from ClapTrap and ScavTrap.
 *
 * Additional ability:
 *  - highFivesGuys(): prints a positive high-five request.
 *
 * Proper inheritance chaining is shown in construction and destruction:
 * ClapTrap is constructed first, followed by FragTrap. Destruction occurs
 * in reverse order.
 */

#include "FragTrap.hpp"
#include <iostream>

/* Constructors / Destructor */

FragTrap::FragTrap() : ClapTrap("default") {
    _hitPoints = 100;
    _energyPoints = 100;
    _attackDamage = 30;
    std::cout << "FragTrap default-constructed: " << _name << std::endl;
}

FragTrap::FragTrap(const std::string& name) : ClapTrap(name) {
    _hitPoints = 100;
    _energyPoints = 100;
    _attackDamage = 30;
    std::cout << "FragTrap constructed with name: " << _name << std::endl;
}

FragTrap::FragTrap(const FragTrap& other) : ClapTrap(other) {
    *this = other;
    std::cout << "FragTrap copy-constructed from: " << other._name << std::endl;
}

FragTrap& FragTrap::operator=(const FragTrap& other) {
    if (this != &other) {
        ClapTrap::operator=(other);
    }
    std::cout << "FragTrap assigned from: " << other._name << std::endl;
    return *this;
}

FragTrap::~FragTrap() {
    std::cout << "FragTrap destroyed: " << _name << std::endl;
}

/* Actions */

void FragTrap::attack(const std::string& target) {
    if (_hitPoints <= 0) {
        std::cout << "FragTrap " << _name << " cannot attack: no hit points left.\n";
        return;
    }
    if (_energyPoints <= 0) {
        std::cout << "FragTrap " << _name << " cannot attack: no energy left.\n";
        return;
    }
    _energyPoints -= 1;
    std::cout << "FragTrap " << _name
              << " launches an attack on " << target
              << ", dealing " << _attackDamage
              << " points of damage! (EN left: " << _energyPoints << ")\n";
}

void FragTrap::highFivesGuys() {
    std::cout << "FragTrap " << _name << " requests a positive high five! ✋\n";
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:26:01 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/03 14:14:33 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

/*Constructor / Destructor */

ClapTrap::ClapTrap()
: _name("default"), _hitPoints(10), _energyPoints(10), _attackDamage(0)
{
    std::cout << "ClapTrap constructed with a name: " << _name << std::endl;
}

ClapTrap::ClapTrap(const std::string& name)
: _name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0) {
    std::cout << "ClapTrap constructed with name: " << _name << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& other)
: _name(other._name),
  _hitPoints(other._hitPoints),
  _energyPoints(other._energyPoints),
  _attackDamage(other._attackDamage) {
    std::cout << "ClapTrap copy-constructed from: " << other._name << std::endl;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& other) {
    if (this != &other) {
        _name = other._name;
        _hitPoints = other._hitPoints;
        _energyPoints = other._energyPoints;
        _attackDamage = other._attackDamage;
    }
    std::cout << "ClapTrap assigned from: " << other._name << std::endl;
    return *this;
}

ClapTrap::~ClapTrap() {
    std::cout << "ClapTrap destroyed: " << _name << std::endl;
}

/* Actions */
void ClapTrap::attack(const std::string& target) {
    if (_hitPoints <= 0) {
        std::cout << "ClapTrap " << _name << " cannot attack: no hit points left.\n";
        return;
    }
    if (_energyPoints <= 0) {
        std::cout << "ClapTrap " << _name << " cannot attack: no energy left.\n";
        return;
    }
    _energyPoints -= 1;
    std::cout << "ClapTrap " << _name
              << " attacks " << target
              << ", causing " << _attackDamage
              << " points of damage! (EN left: " << _energyPoints << ")\n";
}

void ClapTrap::takeDamage(unsigned int amount) {
    if (_hitPoints <= 0) {
        std::cout << "ClapTrap " << _name << " is already at 0 HP; further damage has no effect.\n";
        return;
    }
    // clamp down to zero
    int newHP = _hitPoints - static_cast<int>(amount);
    if (newHP < 0) newHP = 0;
    std::cout << "ClapTrap " << _name
              << " takes " << amount
              << " points of damage! (HP: " << _hitPoints << " -> " << newHP << ")\n";
    _hitPoints = newHP;
}

void ClapTrap::beRepaired(unsigned int amount) {
    if (_hitPoints <= 0) {
        std::cout << "ClapTrap " << _name << " cannot repair: no hit points (knocked out).\n";
        return;
    }
    if (_energyPoints <= 0) {
        std::cout << "ClapTrap " << _name << " cannot repair: no energy left.\n";
        return;
    }
    _energyPoints -= 1;
    // We allow HP to grow unbounded unless your subject requires a cap (it doesn't).
    int newHP = _hitPoints + static_cast<int>(amount);
    std::cout << "ClapTrap " << _name
              << " repairs itself for " << amount
              << " HP (HP: " << _hitPoints << " -> " << newHP
              << ", EN left: " << _energyPoints << ")\n";
    _hitPoints = newHP;
}
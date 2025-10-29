/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:03:32 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/02 12:14:15 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"
#include <iostream>

/**
 * @file HumanB.cpp
 * @brief Implements HumanB: may not have a weapon; can be assigned one later.
 */

HumanB::HumanB(const std::string& name)
    : _name(name), _weapon(NULL) {}

HumanB::~HumanB() {}

void HumanB::setWeapon(Weapon& weapon) {
    _weapon = &weapon;
}

void HumanB::attack() const {
    if (_weapon) {
        std::cout << _name << " attacks with their " << _weapon->getType() << std::endl;
    } else {
        std::cout << _name << " has no weapon" << std::endl;
    }
}

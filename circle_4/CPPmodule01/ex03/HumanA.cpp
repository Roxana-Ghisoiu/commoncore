/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:57:08 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/02 12:06:14 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"
#include <iostream>

/**
 * @file HumanA.cpp
 * @brief Implements HumanA: always has a valid Weapon reference and can attack.
 */

HumanA::HumanA(const std::string& name, Weapon& weapon)
    : _name(name), _weapon(weapon) {}

HumanA::~HumanA() {}

void HumanA::attack() const {
    std::cout << _name << " attacks with their " << _weapon.getType() << std::endl;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:04:04 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/02 11:24:12 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

/**
* @brief Implements the functions of the Weapon class.
 *
 * This file contains the constructor, destructor, and
 * the getter/setter for the weapon type.
 */
Weapon::Weapon() {}

Weapon::Weapon(const std::string& type) : _type(type) {}

Weapon::~Weapon() {}

void Weapon::setType(const std::string& newType) {
    _type = newType;
}

const std::string& Weapon::getType() const {
    return _type;
}
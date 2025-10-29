/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:52:46 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/08 14:06:59 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"
#include <iostream>

/**
 * Default constructor: sets type to "cure".
 */
Cure::Cure() : AMateria("cure") {}

/**
 * Copy constructor.
 */
Cure::Cure(const Cure &other) : AMateria(other) {}

/**
 * Copy assignment.
 */
Cure &Cure::operator=(const Cure &other)
{
    if (this != &other)
        this->type = other.type;
    return *this;
}

/**
 * Clone this Cure (caller owns the returned pointer).
 */
AMateria *Cure::clone() const
{
    return new Cure(*this);
}

/**
 * Use effect: prints "* heals <name>'s wounds *".
 */
void Cure::use(ICharacter &other)
{
    std::cout << "* heals " << other.getName() << "'s wounds *" << std::endl;
}

/**
 * Destructor.
 */
Cure::~Cure() {}

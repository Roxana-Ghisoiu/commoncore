/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:54:27 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/08 14:07:26 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"
#include <iostream>

/** Default constructor: sets type to "ice". */
Ice::Ice() : AMateria("ice") {}

/** Copy constructor. */
Ice::Ice(const Ice &other) : AMateria(other) {}

/** Copy assignment. */
Ice &Ice::operator=(const Ice &other)
{
    if (this != &other)
        this->type = other.type;
    return *this;
}

/** Clone this Ice (caller owns the returned pointer). */
AMateria *Ice::clone() const
{
    return new Ice(*this);
}

/** Use effect: prints "* shoots an ice bolt at <name> *". */
void Ice::use(ICharacter &other)
{
    std::cout << "* shoots an ice bolt at " << other.getName() << " *" << std::endl;
}

/** Destructor. */
Ice::~Ice() {}
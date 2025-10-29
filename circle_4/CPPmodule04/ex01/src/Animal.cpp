/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:27:12 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/04 14:54:37 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** @brief Implementation of the base polymorphic class Animal (Module 04 — ex00).
 *
 * @details
 * Provides the definitions for Animal’s canonical form (default constructor,
 * copy constructor, copy assignment operator, destructor) and member functions.
 * Each constructor and the destructor prints a class-specific message so that
 * object lifetime can be observed during tests, as required by the subject.
 * The default constructor initializes `type` to "Animal". The explicit
 * constructor allows setting a custom `type`. `makeSound()` prints a generic
 * placeholder sound meant to be overridden by derived classes.
 */

#include "Animal.hpp"
#include <iostream>

// Constructor
Animal::Animal() : type("Animal")
{
    std::cout << "[Animal] Default ctor\n";
}

// Copy constructor
Animal::Animal(const Animal& other) : type(other.type)
{
    std::cout << "[Animal] Copy ctor\n";
}

// Copy assignment operator
Animal& Animal::operator=(const Animal& other)
{
    std::cout << "[Animal] Copy assign\n";
    if (this != &other)
    {
        this->type = other.type;
    }
    return *this;
}

// Destructor
Animal::~Animal()
{
    std::cout << "[Animal] dctor\n";
}

// Explicit type constructor
Animal::Animal(const std::string& t) : type(t)
{
    std::cout << "[Animal] Type ctor(" << type << ")\n";
}

// Methods
void Animal::makeSound() const
{
    std::cout << "[Animal] generic animal noise\n";
}

const std::string& Animal::getType() const
{
    return type;
}
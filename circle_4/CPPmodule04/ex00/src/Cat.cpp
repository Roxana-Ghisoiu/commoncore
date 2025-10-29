/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:54:58 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/04 14:58:02 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file Cat.cpp
 * @brief Implementation of the Cat class (Module 04 — ex00).
 *
 * @details
 * Defines the concrete **Cat** class that derives from **Animal**.
 * - The default constructor initializes the base with type `"Cat"`.
 * - Canonical form is provided (default ctor, copy ctor, copy assignment, dtor),
 *   each printing a class-specific message as required by the subject.
 * - `makeSound()` overrides the base behavior to output a cat sound.
 */

#include "Cat.hpp"
#include <iostream>

// Canonical form
Cat::Cat() : Animal("Cat") {
    std::cout << "[Cat] Default ctor\n";
}

Cat::Cat(const Cat& other) : Animal(other) {
    std::cout << "[Cat] Copy ctor\n";
}

Cat& Cat::operator=(const Cat& other) {
    std::cout << "[Cat] Copy assign\n";
    if (this != &other) {
        Animal::operator=(other);
    }
    return *this;
}

Cat::~Cat() {
    std::cout << "[Cat] Dtor\n";
}

// Specific
void Cat::makeSound() const {
    std::cout << "[Cat] Meow~ 🐱\n";
}
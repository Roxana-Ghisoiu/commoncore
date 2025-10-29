/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:58:09 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/04 14:59:14 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file Dog.cpp
 * @brief Implementation of the Dog class (Module 04 — ex00).
 *
 * @details
 * Defines the concrete **Dog** class deriving from **Animal**.
 * - The default constructor initializes the base with type `"Dog"`.
 * - Canonical form (default ctor, copy ctor, copy assignment, dtor) is provided,
 *   each printing a class-specific message as required by the subject.
 * - `makeSound()` overrides the base to output a dog sound.
 */

#include "Dog.hpp"
#include <iostream>

// Canonical form
Dog::Dog() : Animal("Dog") {
    std::cout << "[Dog] Default ctor\n";
}

Dog::Dog(const Dog& other) : Animal(other) {
    std::cout << "[Dog] Copy ctor\n";
}

Dog& Dog::operator=(const Dog& other) {
    std::cout << "[Dog] Copy assign\n";
    if (this != &other) {
        Animal::operator=(other);
    }
    return *this;
}

Dog::~Dog() {
    std::cout << "[Dog] Dtor\n";
}

// Specific
void Dog::makeSound() const {
    std::cout << "[Dog] Woof! 🐶\n";
}

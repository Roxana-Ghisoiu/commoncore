/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:59:32 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/04 15:01:16 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file WrongAnimal.cpp
 * @brief Implementation of the intentionally non-polymorphic base (Module 04 — ex00).
 *
 * @details
 * Defines **WrongAnimal** with canonical form and members. This class
 * intentionally omits `virtual` on `makeSound()` (and destructor in the header)
 * to demonstrate lack of dynamic dispatch: calling `makeSound()` through a
 * `WrongAnimal*` that actually points to a `WrongCat` will invoke the base
 * implementation, matching the subject’s requirement for the “wrong” example.
 */

#include "WrongAnimal.hpp"
#include <iostream>

// Canonical form
WrongAnimal::WrongAnimal() : type("WrongAnimal") {
    std::cout << "[WrongAnimal] Default ctor\n";
}
WrongAnimal::WrongAnimal(const WrongAnimal& other) : type(other.type) {
    std::cout << "[WrongAnimal] Copy ctor\n";
}
WrongAnimal& WrongAnimal::operator=(const WrongAnimal& other) {
    std::cout << "[WrongAnimal] Copy assign\n";
    if (this != &other) {
        this->type = other.type;
    }
    return *this;
}
WrongAnimal::~WrongAnimal() {
    std::cout << "[WrongAnimal] Dtor\n";
}

// Specific
WrongAnimal::WrongAnimal(const std::string& t) : type(t) {
    std::cout << "[WrongAnimal] Type ctor (" << type << ")\n";
}
void WrongAnimal::makeSound() const {
    std::cout << "[WrongAnimal] *wrong generic sound*\n";
}
const std::string& WrongAnimal::getType() const {
    return type;
}

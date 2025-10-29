/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:00:44 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/04 15:01:53 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file WrongCat.cpp
 * @brief Implementation of the WrongCat class (Module 04 — ex00).
 *
 * @details
 * Defines **WrongCat**, which derives from **WrongAnimal**. Since
 * `WrongAnimal::makeSound()` is intentionally non-virtual, calling
 * `makeSound()` through a `WrongAnimal*` that points to a `WrongCat`
 * will invoke the **WrongAnimal** implementation, demonstrating the lack
 * of dynamic dispatch in the “wrong” hierarchy.
 *
 * Canonical form (default ctor, copy ctor, copy assignment, dtor) prints
 * class-specific messages so object lifetime can be observed during tests.
 */

#include "WrongCat.hpp"
#include <iostream>

// Canonical form
WrongCat::WrongCat() : WrongAnimal("WrongCat") {
    std::cout << "[WrongCat] Default ctor\n";
}
WrongCat::WrongCat(const WrongCat& other) : WrongAnimal(other) {
    std::cout << "[WrongCat] Copy ctor\n";
}
WrongCat& WrongCat::operator=(const WrongCat& other) {
    std::cout << "[WrongCat] Copy assign\n";
    if (this != &other) {
        WrongAnimal::operator=(other);
    }
    return *this;
}
WrongCat::~WrongCat() {
    std::cout << "[WrongCat] Dtor\n";
}

// Specific
void WrongCat::makeSound() const {
    std::cout << "[WrongCat] meow?? (but base will be called via WrongAnimal*)\n";
}
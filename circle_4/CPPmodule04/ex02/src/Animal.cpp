/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:27:12 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/05 13:56:24 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file Animal.cpp
 * @brief Definitions for the abstract base class Animal (Module 04 — ex02).
 *
 * Provides canonical form (default ctor, copy ctor, copy assign, dtor)
 * and getType(). makeSound() is pure virtual in the header (no definition here).
 */

#include "Animal.hpp"
#include <iostream>

Animal::Animal() : type("Animal") {
    std::cout << "[Animal] Default ctor\n";
}

Animal::Animal(const Animal& other) : type(other.type) {
    std::cout << "[Animal] Copy ctor\n";
}

Animal& Animal::operator=(const Animal& other) {
    std::cout << "[Animal] Copy assign\n";
    if (this != &other)
        type = other.type;
    return *this;
}

Animal::~Animal() {
    std::cout << "[Animal] dctor\n";
}

Animal::Animal(const std::string& t) : type(t) {
    std::cout << "[Animal] Type ctor(" << type << ")\n";
}

const std::string& Animal::getType() const {
    return type;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:20:20 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/05 14:50:36 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file Dog.cpp
 * @brief Definitions for Dog with Brain composition and deep copy.
 */

#include "Dog.hpp"
#include "Brain.hpp"
#include <iostream>

Dog::Dog() : Animal("Dog"), _brain(new Brain()) {
    std::cout << "[Dog] Default constructor called\n";
}

Dog::Dog(const Dog& other) : Animal(other), _brain(new Brain(*other._brain)) {
    std::cout << "[Dog] Copy constructor called\n";
}

Dog& Dog::operator=(const Dog& other) {
    std::cout << "[Dog] Copy assignment operator called\n";
    if (this != &other) {
        Animal::operator=(other);
        Brain* newBrain = new Brain(*other._brain);
        delete _brain;
        _brain = newBrain;
    }
    return *this;
}

Dog::~Dog() {
    std::cout << "[Dog] Destructor called\n";
    delete _brain;
}

void Dog::makeSound() const {
    std::cout << "[Dog] Woof! 🐶\n";
}

const std::string& Dog::getIdea(std::size_t index) const {
    return _brain->getIdea(index);
}

void Dog::setIdea(std::size_t index, const std::string& idea) {
    _brain->setIdea(index, idea);
}
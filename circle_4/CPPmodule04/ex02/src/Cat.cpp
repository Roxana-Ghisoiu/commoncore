/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:21:20 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/05 12:53:48 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file Cat.cpp
 * @brief Definitions for Cat with Brain composition and deep copy.
 */

#include "Cat.hpp"
#include <iostream>

Cat::Cat() : Animal("Cat"), _brain(new Brain()) {
    std::cout << "[Cat] Default constructor called\n";
}

Cat::Cat(const Cat& other) : Animal(other), _brain(new Brain(*other._brain)) {
    std::cout << "[Cat] Copy constructor called\n";
}

Cat& Cat::operator=(const Cat& other) {
    std::cout << "[Cat] Copy assignment operator called\n";
    if (this != &other) {
        Animal::operator=(other);
        Brain* newBrain = new Brain(*other._brain);
        delete _brain;
        _brain = newBrain;
    }
    return *this;
}

Cat::~Cat() {
    std::cout << "[Cat] Destructor called\n";
    delete _brain;
}

void Cat::makeSound() const {
    std::cout << "[Cat] Meow~ 🐱\n";
}

const std::string& Cat::getIdea(std::size_t index) const {
    return _brain->getIdea(index);
}

void Cat::setIdea(std::size_t index, const std::string& idea) {
    _brain->setIdea(index, idea);
}
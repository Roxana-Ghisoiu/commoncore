/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 11:29:30 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/05 12:02:46 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file Brain.cpp
 * @brief Definitions for the Brain class.
 *
 * Requirements covered:
 * - Print specific messages in constructors, copy/assign and destructor.
 * - Deep copy semantics (copy constructor and copy-assignment copy all ideas).
 * - Safe accessors: getIdea returns a const reference (no copy); setIdea writes.
 * - Out-of-range handling: getIdea returns a static empty string; setIdea ignores.
 */

#include "Brain.hpp"
#include <iostream>

Brain::Brain() {
    std::cout << "[Brain] Default constructor called\n";
    for (std::size_t i = 0; i < 100; ++i)
        _ideas[i].clear();
}

Brain::Brain(const Brain& other) {
    std::cout << "[Brain] Copy constructor called\n";
    for (std::size_t i = 0; i < 100; ++i)
        _ideas[i] = other._ideas[i];
}

Brain& Brain::operator=(const Brain& other) {
    std::cout << "[Brain] Copy assignment operator called\n";
    if (this != &other) {
        for (std::size_t i = 0; i < 100; ++i)
            _ideas[i] = other._ideas[i];
    }
    return *this;
}

Brain::~Brain() {
    std::cout << "[Brain] Destructor called\n";
}

const std::string& Brain::getIdea(std::size_t index) const {
    static const std::string empty;
    if (index < 100)
        return _ideas[index];
    return empty;
}

void Brain::setIdea(std::size_t index, const std::string& idea) {
    if (index < 100)
        _ideas[index] = idea;
}
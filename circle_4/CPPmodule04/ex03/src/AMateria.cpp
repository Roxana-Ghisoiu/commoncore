/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:49:37 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/08 14:04:26 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

/**
 * Default-constructs an empty AMateria (type = "").
 */
AMateria::AMateria() : type("") {}

/**
 * Constructs an AMateria with a given type string.
 * @param type Materia type identifier (e.g., "ice", "cure").
 */
AMateria::AMateria(std::string const &type) : type(type) {}

/**
 * Copy-constructs from another AMateria (copies type).
 * @param other Source AMateria.
 */
AMateria::AMateria(const AMateria &other) : type(other.type) {}

/**
 * Copy-assigns from another AMateria (copies type).
 * @param other Source AMateria.
 * @return Reference to *this.
 */
AMateria &AMateria::operator=(const AMateria &other)
{
    if (this != &other)
        this->type = other.type;
    return *this;
}

/**
 * Gets the Materia type string.
 * @return Read-only reference to internal type.
 */
std::string const &AMateria::getType() const { return type; }

/**
 * Hook called when the materia is used on a target.
 * Base implementation is a no-op; derived classes override.
 * @param target Target character.
 */

 void AMateria::use(ICharacter& target)
{
    (void)target;
}

/**
 * Destroys the AMateria.
 */
AMateria::~AMateria() {}

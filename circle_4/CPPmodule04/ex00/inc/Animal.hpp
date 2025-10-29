/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:24:04 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/04 13:51:37 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** @brief Base polymorphic interface for animals (Module 04 — ex00).
 *
 * @details
 * Defines the base class **Animal** with a protected `std::string type` used by
 * derived classes (**Dog**, **Cat**). The class provides:
 *   - a **virtual destructor** to allow safe polymorphic deletion,
 *   - a **virtual** `makeSound() const` that derived classes override,
 *   - an accessor `getType()` returning the animal type.
 *
 * Constructors and the destructor are expected to print **class-specific
 * messages** (as required by the subject) so object lifetime can be observed
 * during tests.
 *
 * The class also exposes an **explicit** constructor that initializes `type`.
 */

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <string>

class Animal
{
protected:
    std::string type;

public:
    Animal();
    Animal(const Animal& other);
    Animal& operator=(const Animal& other);
    virtual ~Animal();

    explicit Animal(const std::string& type);
    virtual void makeSound() const;
    const std::string& getType() const;
};

#endif
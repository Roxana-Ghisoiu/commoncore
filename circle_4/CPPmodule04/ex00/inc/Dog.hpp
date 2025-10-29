/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:01:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/04 14:04:00 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file Dog.hpp
 * @brief Concrete Animal derived class for Module 04 — ex00.
 *
 * @details
 * Declares the **Dog** class which publicly inherits from **Animal**.
 * Per the subject, the Dog constructor must initialize the protected `type`
 * field to `"Dog"`. All constructors and the destructor must print
 * **class-specific messages** so object lifetime can be observed in tests.
 *
 * The `makeSound()` member function overrides `Animal::makeSound()` and should
 * output an appropriate dog sound (e.g., "Woof").
 */

#ifndef DOG_HPP
# define DOG_HPP

#include "Animal.hpp"
#include <string>

class Dog : public Animal
{
public:
    Dog();
    Dog(const Dog& other);
    Dog& operator=(const Dog& other);
    virtual ~Dog();

    virtual void makeSound() const;
};

#endif
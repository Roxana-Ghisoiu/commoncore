/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:49:12 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/04 14:00:50 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file Cat.hpp
 * @brief Concrete Animal derived class for Module 04 — ex00.
 *
 * @details
 * Declares the **Cat** class which inherits from **Animal**. According to the
 * subject, the Cat constructor must initialize the protected `type` field to
 * `"Cat"` and all constructors/destructor must print class-specific messages
 * so object lifetime can be observed during tests.
 *
 * The `makeSound()` member function overrides `Animal::makeSound()` and should
 * output an appropriate cat sound (e.g., "Meow").
 */

#ifndef CAT_HPP
# define CAT_HPP

#include "Animal.hpp"
#include <string>

class Cat : public Animal
{
public:
    Cat();
    Cat(const Cat& other);
    Cat& operator=(const Cat& other);
    virtual ~Cat();

    virtual void makeSound() const;
};

#endif
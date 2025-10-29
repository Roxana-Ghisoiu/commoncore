/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:16:33 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/04 14:26:22 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file WrongCat.hpp
 * @brief Derived class used to demonstrate missing polymorphism (Module 04 — ex00).
 *
 * @details
 * Declares **WrongCat**, which inherits from **WrongAnimal**. The base class
 * intentionally does NOT declare `makeSound()` as `virtual`, so calling
 * `makeSound()` through a `WrongAnimal*` that actually points to a `WrongCat`
 * will invoke the **WrongAnimal** implementation, not this one. This matches
 * the subject’s requirement that the "wrong" version outputs the base sound.
 *
 * Constructors and the destructor should print class-specific messages
 * (per subject) to make object lifetime visible during tests.
 */

#ifndef WRONGCAT_HPP
# define WRONGCAT_HPP

#include "WrongAnimal.hpp"
#include <string>

class WrongCat : public WrongAnimal
{
public:
    WrongCat();
    WrongCat(const WrongCat& other);
    WrongCat& operator=(const WrongCat& other);
    ~WrongCat();

    void makeSound() const;
};

#endif
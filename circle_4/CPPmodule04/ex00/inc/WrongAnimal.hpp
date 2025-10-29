/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:09:35 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/04 14:13:14 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file WrongAnimal.hpp
 * @brief Intentionally non-polymorphic base class (Module 04 — ex00).
 *
 * @details
 * Declares **WrongAnimal**, a base class that intentionally omits `virtual`
 * on both the destructor and `makeSound()` to illustrate what happens when a
 * base class is used without polymorphism. If you call `makeSound()` through a
 * `WrongAnimal*` pointing to a `WrongCat`, the **WrongAnimal** version will be
 * called instead of the derived one.
 *
 * The class stores a protected `std::string type` and exposes:
 *  - canonical form (default ctor, copy ctor, copy assignment, dtor),
 *  - an explicit constructor that sets `type`,
 *  - `makeSound()` (non-virtual) and `getType()`.
 */

#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP

#include <string>

class WrongAnimal
{
protected:
    std::string type;

public:
    WrongAnimal();
    WrongAnimal(const WrongAnimal& other);
    WrongAnimal& operator=(const WrongAnimal& other);
    ~WrongAnimal(); // intentionally non-virtual

    explicit WrongAnimal(const std::string& type);
    void makeSound() const; // intentionally non-virtual
    const std::string& getType() const;
};

#endif
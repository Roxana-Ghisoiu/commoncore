/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:24:04 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/05 15:26:56 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** @brief Abstract base class for Module 04 — ex02.
 *
 * The Animal class is intentionally made abstract: the interface function
 * `makeSound()` is declared pure virtual (`= 0`), so `Animal` cannot be
 * instantiated directly. Concrete subclasses (e.g., Dog, Cat) must implement
 * this function.
 *
 * Polymorphic deletion is supported via a virtual destructor, allowing:
 *   `Animal* p = new Dog(); delete p;`
 * to call derived destructors in the correct order.
 *
 * The class also stores a protected `type` string and exposes:
 *   - `getType()` for read-only access,
 *   - an explicit constructor `Animal(const std::string&)` for initializing it.
 *
 * As required by the subject, constructors and the destructor should print
 * diagnostic messages (implemented in Animal.cpp) to observe object lifetime
 * and destruction order during tests.
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
    virtual void makeSound() const = 0;
    const std::string& getType() const;
};

typedef Animal AAnimal; 

#endif
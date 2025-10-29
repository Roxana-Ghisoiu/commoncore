/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 15:02:24 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/04 15:04:08 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file main.cpp
 * @brief Test suite for Module 04 — ex00 (polymorphism and “wrong” example).
 *
 * @details
 * Runs several scenarios:
 *  - Proper polymorphism with Animal / Dog / Cat: `makeSound()` dispatches
 *    dynamically and prints the derived sounds via base pointers.
 *  - “Wrong” hierarchy with WrongAnimal / WrongCat: `makeSound()` is
 *    intentionally non-virtual in the base, so calling through a base pointer
 *    prints the base sound (as required by the subject).
 *  - Extra copy/assignment tests to validate canonical form behavior.
 *
 * @note In the “wrong” hierarchy, deleting through a base pointer with a
 * non-virtual destructor is undefined behavior in real code; this is used
 * here only for didactic purposes.
 */

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include <iostream>

int main() {
    std::cout << "=== Polymorphism demo ===\n";
    const Animal* meta = new Animal();
    const Animal* j = new Dog();
    const Animal* i = new Cat();

    std::cout << j->getType() << std::endl;
    std::cout << i->getType() << std::endl;

    i->makeSound();    // Cat
    j->makeSound();    // Dog
    meta->makeSound(); // Animal

    delete meta;
    delete j;
    delete i;

    std::cout << "\n=== Wrong polymorphism demo ===\n";
    const WrongAnimal* wmeta = new WrongAnimal();
    const WrongAnimal* wi = new WrongCat();

    std::cout << wi->getType() << std::endl;

    // Calls WrongAnimal's method (not virtual)
    wi->makeSound();
    wmeta->makeSound();

    // Warning: deleting via non-virtual base destructor is UB in real code.
    delete wmeta;
    delete wi;

    std::cout << "\n=== Copy / assign tests ===\n";
    Dog d1;
    Dog d2 = d1;        // copy constructor
    Dog d3;
    d3 = d1;            // copy assignment

    Cat c1;
    Cat c2(c1);
    Cat c3;
    c3 = c1;

    return 0;
}
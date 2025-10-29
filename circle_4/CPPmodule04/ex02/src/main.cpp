/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+      */
/*   By: rghisoiu <rghisoiu@student.42luxembourg>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:22:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/05 17:25:00 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Tests for Module 04 — ex02 (Animal is abstract).
 *
 * Plan:
 *  1) Subject snippet: new Dog/Cat via AAnimal* and delete (no leaks).
 *  2) Array of AAnimal* with half Dogs / half Cats; makeSound() then delete.
 *  3) Deep copy proofs: Dog (copy-ctor), Cat (copy-assign) using Brain ideas.
 *
 * Note: If you try to instantiate the base, it should fail in ex02:
 *   // const AAnimal* a = new AAnimal(); // error if uncommented
 *   // AAnimal b;                        // error if uncommented
 */

#include <iostream>
#include <cstddef>
#include "Animal.hpp" // provides Animal and the alias typedef Animal AAnimal;
#include "Dog.hpp"
#include "Cat.hpp"

#define NBR_ANIMALS 4

int main() {
    {
        const AAnimal* j = new Dog();
        const AAnimal* i = new Cat();
        delete j; // should not create a leak
        delete i;
    }

    std::cout << "=== Array of AAnimal* (half Dogs / half Cats) ===\n";
    {
        AAnimal* zoo[NBR_ANIMALS];

        for (std::size_t k = 0; k < NBR_ANIMALS; ++k) {
            if (k < NBR_ANIMALS / 2) zoo[k] = new Dog();
            else                     zoo[k] = new Cat();
        }

        for (std::size_t k = 0; k < NBR_ANIMALS; ++k)
            zoo[k]->makeSound();

        for (std::size_t k = 0; k < NBR_ANIMALS; ++k)
            delete zoo[k];
    }

    std::cout << "\n=== Deep copy test: Dog (copy constructor) ===\n";
    {
        Dog d1;
        d1.setIdea(0, "chase cats");
        Dog d2 = d1;
        std::cout << "d1 idea[0]: " << d1.getIdea(0) << "\n";
        std::cout << "d2 idea[0]: " << d2.getIdea(0) << "\n";
        d2.setIdea(0, "sleep");
        std::cout << "d1 idea[0] after d2 change: " << d1.getIdea(0) << "\n";
        std::cout << "d2 idea[0] after change:    " << d2.getIdea(0) << "\n";
    }

    std::cout << "\n=== Deep copy test: Cat (copy assignment) ===\n";
    {
        Cat c1;
        c1.setIdea(1, "steal tuna");
        Cat c2;
        c2 = c1;
        std::cout << "c1 idea[1]: " << c1.getIdea(1) << "\n";
        std::cout << "c2 idea[1]: " << c2.getIdea(1) << "\n";
        c2.setIdea(1, "nap");
        std::cout << "c1 idea[1] after c2 change: " << c1.getIdea(1) << "\n";
        std::cout << "c2 idea[1] after change:    " << c2.getIdea(1) << "\n";
    }

    return 0;
}
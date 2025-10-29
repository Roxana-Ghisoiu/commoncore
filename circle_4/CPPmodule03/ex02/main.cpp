/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:15:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/04 10:40:36 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file main.cpp
 * @brief Extended test for CPP03/ex02 (FragTrap).
 *
 * This test covers:
 *  - Construction and destruction chaining.
 *  - Normal attacks, taking damage, repairing.
 *  - Special ability highFivesGuys().
 *  - Energy consumption until 0.
 *  - Behavior when no energy left.
 *  - Behavior when hit points reach 0.
 */

#include <iostream>
#include "ClapTrap.hpp"
#include "FragTrap.hpp"

int main() {
    std::cout << "\n=== ClapTrap basic test ===\n";
    ClapTrap clap("BasicClap");
    clap.attack("Dummy");
    clap.takeDamage(5);
    clap.beRepaired(3);

    std::cout << "\n=== FragTrap extended test ===\n";
    FragTrap frag("Fiona");
    frag.attack("Intruder");
    frag.takeDamage(30);
    frag.beRepaired(15);
    frag.highFivesGuys();

    std::cout << "\n-- Testing energy consumption --\n";
    for (int i = 0; i < 105; i++) { // FragTrap starts with 100 energy
        frag.attack("Training dummy");
    }

    std::cout << "\n-- Testing actions with 0 energy --\n";
    frag.beRepaired(5);
    frag.attack("Dummy again");

    std::cout << "\n-- Testing when HP drops to 0 --\n";
    frag.takeDamage(500);   // should reduce HP to 0
    frag.attack("Dummy after KO");
    frag.beRepaired(10);

    std::cout << "\n=== End of tests ===\n";
    return 0;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:10:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/09 13:03:50 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** @brief Extended test for CPP03/ex01 (ScavTrap).
 * This test covers:
 *  - Construction and destruction chaining.
 *  - Normal attacks, taking damage, repairing.
 *  - Special ability guardGate().
 *  - Energy consumption until 0.
 *  - Behavior when no energy left.
 *  - Behavior when hit points reach 0.
 */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main() {
    std::cout << "\n=== ClapTrap basic test ===\n";
    ClapTrap clap("BasicClap");
    clap.attack("Dummy");
    clap.takeDamage(5);
    clap.beRepaired(3);

    std::cout << "\n=== ScavTrap extended test ===\n";
    ScavTrap scav("Serena");
    scav.attack("Intruder");
    scav.takeDamage(20);
    scav.beRepaired(10);
    scav.guardGate();

    std::cout << "\n-- Testing energy consumption --\n";
    for (int i = 0; i < 55; i++) {
        scav.attack("Training dummy");
    }

    std::cout << "\n-- Testing actions with 0 energy --\n";
    scav.beRepaired(5);
    scav.attack("Dummy again");

    std::cout << "\n-- Testing when HP drops to 0 --\n";
    scav.takeDamage(200);   // should reduce HP to 0
    scav.attack("Dummy after KO");
    scav.beRepaired(10);

    std::cout << "\n=== End of tests ===\n";
    return 0;
}
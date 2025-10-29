/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:00:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/04 12:15:00 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** @brief Extended test for CPP03/ex03 (DiamondTrap).
 *
 * This test covers:
 *  - Construction and destruction chaining (ClapTrap, ScavTrap, FragTrap, DiamondTrap).
 *  - Attack behavior (delegated to ScavTrap).
 *  - Inherited takeDamage() and beRepaired() from ClapTrap.
 *  - Special ability whoAmI(), printing both DiamondTrap and ClapTrap names.
 *  - Copy constructor and copy assignment operator.
 *  - Energy exhaustion test (EP runs out).
 *  - HP exhaustion test (HP reduced to 0).
 */

#include <iostream>
#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include "DiamondTrap.hpp"

int main() {
    std::cout << "\n=== Default constructor: base then derived messages ===\n";
    DiamondTrap d1;
    d1.attack("Enemy1");
    d1.takeDamage(30);
    d1.beRepaired(20);
    d1.whoAmI();

    std::cout << "\n=== Parameterized constructor: base + derived message ===\n";
    DiamondTrap d2("Shiny");
    d2.attack("Enemy2");
    d2.takeDamage(50);
    d2.beRepaired(25);
    d2.whoAmI();

    std::cout << "\n=== Copy constructor ===\n";
    DiamondTrap d3(d2);
    d3.attack("Enemy3");
    d3.whoAmI();

    std::cout << "\n=== Copy assignment ===\n";
    DiamondTrap d4;
    d4 = d1;
    d4.attack("Enemy4");
    d4.whoAmI();

    std::cout << "\n=== Energy exhaustion test ===\n";
    DiamondTrap d5("NoEnergy");
    for (int i = 0; i < 55; i++) {
        d5.attack("Training dummy");
    }

    std::cout << "\n=== HP exhaustion test ===\n";
    DiamondTrap d6("NoHP");
    d6.takeDamage(200);   // Should drop HP to 0
    d6.attack("After KO");
    d6.beRepaired(10);
    d6.whoAmI();

    std::cout << "\n=== End of DiamondTrap tests ===\n";
    return 0;
}

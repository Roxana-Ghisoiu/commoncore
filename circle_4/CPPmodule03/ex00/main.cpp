/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:20:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/03 14:07:19 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file main.cpp
 * @brief Test program for ClapTrap (CPP03/ex00).
 *
 * Creates two ClapTrap objects and tests:
 *  - attacking until energy runs out,
 *  - taking and repairing damage,
 *  - trying to act without energy or hit points.
 */

#include "ClapTrap.hpp"

int main() {
    ClapTrap clap1("Attacker");
    ClapTrap clap2("Defender");

    clap1.attack("Defender");
    clap2.takeDamage(3);

    clap2.beRepaired(2);
    clap2.attack("Attacker");

    clap1.takeDamage(5);
    clap1.beRepaired(4);
    clap1.attack("Defender");

    // drain all energy points (10 total)
    for (int i = 0; i < 10; i++)
        clap1.attack("Defender");

    // now clap1 has no energy left
    clap1.beRepaired(1);

    // take lethal damage
    clap1.takeDamage(20);

    // cannot attack or repair anymore (HP = 0)
    clap1.attack("Defender");
    clap1.beRepaired(1);

    return 0;
}
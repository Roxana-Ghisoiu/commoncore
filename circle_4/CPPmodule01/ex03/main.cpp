/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:08:36 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/02 12:26:12 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"
#include "HumanB.hpp"
#include "Weapon.hpp"

/**
 * @brief Entry point of the program demonstrating HumanA and HumanB behavior.
 *
 * The program creates two scenarios:
 * - HumanA is always constructed with a weapon and attacks with it.
 * - HumanB is constructed without a weapon, but one can be assigned later.
 *
 * In both cases, changing the weapon type via Weapon::setType()
 * will be reflected in subsequent attacks.
 */

int main(void)
{
    {
        Weapon club = Weapon("crude spiked club");
        HumanA bob("Bob", club);
        bob.attack();
        club.setType("some other type of club");
        bob.attack();
    }
    {
        Weapon club = Weapon("crude spiked club");
        HumanB jim("Jim");
        jim.setWeapon(club);
        jim.attack();
        club.setType("some other type of club");
        jim.attack();
    }
    return 0;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:16:41 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/03 15:31:07 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** @brief Declaration of the ScavTrap class (CPP03/ex01).
 *
 * ScavTrap is a derived class from ClapTrap with modified stats and behaviors.
 * Attributes (inherited from ClapTrap) are initialized as:
 *  - Hit points: 100
 *  - Energy points: 50
 *  - Attack damage: 20
 *
 * Constructors, destructor, and the attack() function display messages 
 * different from ClapTrap to emphasize individuality.
 *
 * Additional feature:
 *  - guardGate(): enables Gate Keeper mode, printing a specific message.
 *
 * Construction and destruction demonstrate proper inheritance chaining:
 * ClapTrap is constructed first, then ScavTrap. Destruction occurs in reverse.
 */

#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

# include "ClapTrap.hpp"

class ScavTrap : public ClapTrap {
public:
    ScavTrap();
    ScavTrap(const std::string& name);
    ScavTrap(const ScavTrap& other);
    ScavTrap& operator=(const ScavTrap& other);
    ~ScavTrap();

    void attack(const std::string& target);
    void guardGate();
};

#endif
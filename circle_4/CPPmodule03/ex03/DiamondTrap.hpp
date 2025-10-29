/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:30:06 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/04 12:13:58 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** @brief Declaration of the DiamondTrap class (CPP03/ex03).
 *
 * DiamondTrap inherits from both ScavTrap and FragTrap.
 * It has its own private name (same variable name as ClapTrap's),
 * while the ClapTrap subobject uses "<name>_clap_name".
 *
 * Attributes come from parents:
 *  - Hit points: FragTrap (100)
 *  - Energy points: ScavTrap (50)
 *  - Attack damage: FragTrap (30)
 *
 * attack(): uses ScavTrap's behavior.
 * whoAmI(): prints DiamondTrap's name and ClapTrap's name.
 */

#ifndef DIAMONDTRAP_HPP
# define DIAMONDTRAP_HPP

# include "ClapTrap.hpp"
# include "ScavTrap.hpp"
# include "FragTrap.hpp"
# include <string>

class DiamondTrap : virtual public ScavTrap, virtual public FragTrap {
private:
    // Must match the exact variable name used in ClapTrap
    std::string _name;

public:
    DiamondTrap();
    DiamondTrap(const std::string& name);
    DiamondTrap(const DiamondTrap& other);
    DiamondTrap& operator=(const DiamondTrap& other);
    ~DiamondTrap();

    void attack(const std::string& target);
    void whoAmI();
};

#endif
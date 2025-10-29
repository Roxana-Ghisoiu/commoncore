/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 10:11:14 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/04 12:12:47 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/** @brief Declaration of the FragTrap class (CPP03/ex02).
 *
 * FragTrap is a derived class from ClapTrap with modified base attributes:
 *  - Hit points: 100
 *  - Energy points: 100
 *  - Attack damage: 30
 *
 * Constructors, destructor, and the attack() function display different
 * messages compared to ClapTrap to emphasize individuality.
 *
 * Additional feature:
 *  - highFivesGuys(): displays a positive high-five request.
 *
 * Construction and destruction demonstrate proper inheritance chaining:
 * ClapTrap is constructed first, then FragTrap. Destruction occurs in reverse.
 */

#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

# include "ClapTrap.hpp"

class FragTrap : virtual public ClapTrap {
public:
    FragTrap();
    FragTrap(const std::string& name);
    FragTrap(const FragTrap& other);
    FragTrap& operator=(const FragTrap& other);
    ~FragTrap();

    void attack(const std::string& target);
    void highFivesGuys(void);
};

#endif
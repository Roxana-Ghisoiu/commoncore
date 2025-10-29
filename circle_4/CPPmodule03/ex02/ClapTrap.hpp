/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:06:26 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/03 15:26:43 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ClapTrap.hpp
 * @brief Declaration of the ClapTrap class (CPP03/ex00).
 *
 * ClapTrap holds a name, hit points, energy points and attack damage.
 * Actions:
 *  - attack(target): costs 1 energy; prints a message; uses attackDamage as damage.
 *  - takeDamage(amount): reduces hit points (not below zero); prints a message.
 *  - beRepaired(amount): costs 1 energy; increases hit points; prints a message.
 * If hit points == 0 or energy == 0, actions do nothing (but print why).
 * Constructors and destructor print messages when called.
 */

#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

# include <iostream>
# include <string>

class ClapTrap {
protected:
    std::string _name;
    int         _hitPoints;  
    int         _energyPoints; 
    int         _attackDamage; 

public:
    ClapTrap();
    ClapTrap(const std::string& name);
    ClapTrap(const ClapTrap& other);
    ClapTrap& operator=(const ClapTrap& other);
    ~ClapTrap();

    void attack(const std::string& target);
    void takeDamage(unsigned int amount);
    void beRepaired(unsigned int amount);

};

#endif
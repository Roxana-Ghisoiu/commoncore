/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:40:44 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/02 11:57:00 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_HPP
#define HUMANA_HPP
#include <string>
#include "Weapon.hpp"

/**
 * @brief Defines the HumanA class, representing a human that always has a weapon.
 *
 * HumanA is constructed with both a name and a Weapon reference.
 * Because the weapon is a reference, it cannot be null and must always exist.
 * The attack() function displays the human's name and the type of weapon used.
 */
class HumanA
{
private:
    std::string _name;
    Weapon      &_weapon;
public:
    HumanA(const std::string& name, Weapon& weapon);
    ~HumanA();
    void    attack() const;
};

#endif
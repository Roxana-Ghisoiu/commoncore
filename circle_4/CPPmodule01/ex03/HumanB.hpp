/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:40:53 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/02 11:53:47 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
#define HUMANB_HPP
#include <string>
#include "Weapon.hpp"

/**
 * @brief Defines the HumanB class, representing a human that may or may not have a weapon.
 *
 * HumanB is constructed with only a name and no weapon initially.
 * A weapon can be assigned later using setWeapon().
 * The attack() function will display the human's name and their weapon type
 * if a weapon is set, or indicate that the human has no weapon.
 */

class HumanB
{
private:
    std::string _name;
    Weapon*     _weapon;
public:
    HumanB(const std::string& name);
    ~HumanB();
    void    attack() const;
    void    setWeapon(Weapon& weapon);
};

#endif
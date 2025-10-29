/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:57:13 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/02 11:40:30 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
# define WEAPON_HPP

#include <iostream>
#include <string>

/** @brief Defines the Weapon class used in the HumanA and HumanB examples.
 *
 * The Weapon class represents a weapon with a string type.
 * It allows setting and retrieving the type of the weapon.
 * Other classes can hold a reference or a pointer to Weapon
 * to demonstrate object relationships.
 */

class Weapon {
   private:
    std::string _type;

    public:
        Weapon();
        Weapon(const std::string& type);
        ~Weapon();
        void setType (const std::string& newType);
        const std::string&  getType() const;
};

#endif
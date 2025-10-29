/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:32:47 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/08 13:58:50 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "ICharacter.hpp"
#include "AMateria.hpp"
#include <string>

/**
 * Concrete character implementing ICharacter.
 * Holds a 4-slot inventory of AMateria*, equipped in order 0..3.
 * unequip(idx) detaches the pointer without deleting it (stored internally on the “floor”).
 * Copy is deep (clones equipped Materias); destructor frees inventory and stored pointers.
 */
class Character : public ICharacter
{
    private:
        std::string name;
        AMateria *slots[4];
        AMateria *addr[500];
        int unequipCount;
    public:
        Character();
        Character(std::string name);
        Character(const Character &other);
        Character &operator=(const Character &other);
        ~Character();

        std::string const & getName() const;
        void equip(AMateria* m);
        void unequip(int idx);
        void use(int idx, ICharacter& target);
};

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:51:41 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/08 14:06:16 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"
#include "AMateria.hpp"

/**
 * @brief Default-construct an empty Character.
 * Initializes inventory to NULL and clears the internal floor.
 */
Character::Character()
{
    unequipCount = 0;
    for (int i = 0; i < 4; ++i)  slots[i] = NULL;
    for (int i = 0; i < 500; ++i) addr[i]  = NULL;
}

/**
 * @brief Construct a Character with a given name.
 * @param name Character name.
 */
Character::Character(std::string name)
{
    this->name = name;
    unequipCount = 0;
    for (int i = 0; i < 4; ++i)  slots[i] = NULL;
    for (int i = 0; i < 500; ++i) addr[i]  = NULL;
}

/**
 * @brief Copy-construct a Character (deep-copies inventory).
 * @param other Source character.
 */
Character::Character(const Character &other)
{
    this->name = other.name;
    unequipCount = 0;
    for (int i = 0; i < 4; ++i)
        slots[i] = other.slots[i] ? other.slots[i]->clone() : NULL;
    for (int i = 0; i < 500; ++i)
        addr[i] = NULL;
}

/**
 * @brief Copy-assign a Character (deep-copies inventory).
 * Frees current inventory before cloning from source. Floor is reset.
 * @param other Source character.
 * @return Reference to *this.
 */
Character &Character::operator=(const Character &other)
{
    if (this != &other)
    {
        this->name = other.name;
        for (int i = 0; i < 4; ++i)
        {
            if (slots[i])
            {
                delete slots[i];
                slots[i] = NULL;
            }
        }
        for (int i = 0; i < 4; ++i)
            if (other.slots[i])
                slots[i] = other.slots[i]->clone();
        for (int i = 0; i < 500; ++i) addr[i] = NULL;
        unequipCount = 0;
    }
    return *this;
}

/**
 * @brief Get the character name.
 * @return const std::string& Name reference.
 */
std::string const & Character::getName() const
{
    return name;
}

/**
 * @brief Equip a Materia into the first available slot (0..3).
 * @param m Materia pointer (ignored if NULL or inventory is full).
 */
void Character::equip(AMateria* m)
{
    if (!m) return;
    for (int i = 0; i < 4; ++i)
    {
        if (slots[i] == NULL)
        {
            slots[i] = m;
            return;
        }
    }
}

/**
 * @brief Unequip the Materia at index without deleting it.
 * The pointer is stored internally so it can be freed on destruction.
 * @param idx Inventory index (0..3).
 */
void Character::unequip(int idx)
{
    if (idx < 0 || idx >= 4) return;
    if (!slots[idx]) return;

    if (unequipCount < 500)
        addr[unequipCount++] = slots[idx];
    slots[idx] = NULL;
}

/**
 * @brief Use the Materia at index on the target, if present.
 * @param idx Inventory index (0..3).
 * @param target Target character.
 */
void Character::use(int idx, ICharacter& target)
{
    if (idx < 0 || idx >= 4) return;
    if (slots[idx])
        slots[idx]->use(target);
}

/**
 * @brief Destroy the Character.
 * Frees equipped Materias and any stored unequipped pointers.
 */
Character::~Character()
{
    for (int i = 0; i < 4; ++i)
        if (slots[i]) delete slots[i];

    for (int i = 0; i < unequipCount; ++i)
        if (addr[i]) delete addr[i];
}
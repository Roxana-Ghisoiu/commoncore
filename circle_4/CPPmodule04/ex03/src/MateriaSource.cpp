/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:37:29 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/08 14:08:09 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"

/** Default-constructs with all slots set to NULL. */
MateriaSource::MateriaSource()
{
    for (int i = 0; i < 4; ++i)
        slots[i] = NULL;
}

/** Copy-constructs; deep-copies stored templates. */
MateriaSource::MateriaSource(const MateriaSource &other)
{
    for (int i = 0; i < 4; ++i)
        slots[i] = other.slots[i] ? other.slots[i]->clone() : NULL;
}

/** Copy-assigns; clears current and deep-copies from source. */
MateriaSource &MateriaSource::operator=(const MateriaSource &other)
{
    if (this != &other)
    {
        for (int i = 0; i < 4; ++i)
        {
            if (slots[i])
            {
                delete slots[i];
                slots[i] = NULL;
            }
            if (other.slots[i])
                slots[i] = other.slots[i]->clone();
        }
    }
    return *this;
}

/** Learns a Materia by cloning it into the first free slot; deletes the argument. */
void MateriaSource::learnMateria(AMateria* materia)
{
    if (!materia)
        return;
    for (int i = 0; i < 4; ++i)
    {
        if (slots[i] == NULL)
        {
            slots[i] = materia->clone();
            delete materia;
            return;
        }
    }
    delete materia;
}

/** Creates a new Materia by type from stored templates; returns NULL if unknown. */
AMateria* MateriaSource::createMateria(std::string const & type)
{
    for (int i = 0; i < 4; ++i)
    {
        if (slots[i] && slots[i]->getType() == type)
            return slots[i]->clone();
    }
    return NULL;
}

/** Destroys the source; deletes stored templates. */
MateriaSource::~MateriaSource()
{
    for (int i = 0; i < 4; ++i)
    {
        if (slots[i])
        {
            delete slots[i];
            slots[i] = NULL;
        }
    }
}
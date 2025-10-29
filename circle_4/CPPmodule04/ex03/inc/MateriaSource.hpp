/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:36:40 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/08 14:03:03 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP

#include "IMateriaSource.hpp"
#include "AMateria.hpp"
#include <memory>

/**
 * Materia source implementing IMateriaSource.
 * Stores up to 4 learned templates and can create new Materias by type.
 * Copy is deep; destructor releases stored templates.
 */
class MateriaSource : public IMateriaSource
{
    private:
        AMateria *slots[4];
    public:
        MateriaSource();
        MateriaSource(const MateriaSource &other);
        MateriaSource &operator=(const MateriaSource &other);
        ~MateriaSource();

        void learnMateria(AMateria* materia);
        AMateria* createMateria(std::string const & type);
};

#endif
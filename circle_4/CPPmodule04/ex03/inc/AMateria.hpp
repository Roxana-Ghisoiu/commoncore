/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:19:38 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/08 13:58:14 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMATERIA_HPP
#define AMATERIA_HPP

#include "ICharacter.hpp"
#include <string>

/**
 * Abstract base for all Materias.
 * Holds a type string and defines the polymorphic interface:
 * - getType()
 * - clone() (pure virtual)
 * - use(ICharacter&) (base no-op; overridden by concrete Materias like Ice/Cure).
 */
class AMateria
{
    protected:
        std::string type;
    public:
        AMateria();
        AMateria(std::string const & type);
        AMateria(const AMateria &other);
        AMateria &operator=(const AMateria &other);
        virtual ~AMateria();

        std::string const & getType() const;
        virtual AMateria* clone() const = 0;
        virtual void use(ICharacter& target);
};

#endif

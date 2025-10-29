/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:29:38 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/08 14:01:34 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICE_HPP
#define ICE_HPP

#include "AMateria.hpp"
#include "ICharacter.hpp"

/**
 * Concrete Materia of type "ice".
 * clone() returns a new Ice; use() prints "* shoots an ice bolt at <name> *".
 */
class Ice : public AMateria {
public:
	// Canonical
	Ice();
	Ice(const Ice& other);
	Ice& operator=(const Ice& other);
	virtual ~Ice();

	// Polymorphic
	virtual AMateria* clone() const;
	virtual void use(ICharacter& target);
};

#endif
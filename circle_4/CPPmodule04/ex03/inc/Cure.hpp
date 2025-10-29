/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:31:20 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/08 14:01:06 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURE_HPP
#define CURE_HPP

#include "AMateria.hpp"
#include "ICharacter.hpp"

/**
 * Concrete Materia of type "cure".
 * clone() returns a new Cure; use() prints "* heals <name>'s wounds *".
 */
class Cure : public AMateria {
public:
	// Canonical
	Cure();
	Cure(const Cure& other);
	Cure& operator=(const Cure& other);
	virtual ~Cure();

	// Polymorphic
	virtual AMateria* clone() const;
	virtual void use(ICharacter& target);
};

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:56:51 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/08 14:08:45 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Minimal driver matching the subject's example.
 * Builds a MateriaSource (learning Ice/Cure), equips a Character,
 * then uses slot 0 (ice) and slot 1 (cure) on target "bob".
 * Expected output:
 *  * shoots an ice bolt at bob *
 *  * heals bob's wounds *
 */

#include "MateriaSource.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include "Character.hpp"

/**
 * @brief Entry point running the subject's demonstration scenario.
 */
int main()
{
    IMateriaSource* src = new MateriaSource();
    src->learnMateria(new Ice());
    src->learnMateria(new Cure());

    ICharacter* me = new Character("me");

    AMateria* tmp;
    tmp = src->createMateria("ice");
    me->equip(tmp);
    tmp = src->createMateria("cure");
    me->equip(tmp);

    ICharacter* bob = new Character("bob");

    me->use(0, *bob);
    me->use(1, *bob);

    delete bob;
    delete me;
    delete src;

    return 0;
}
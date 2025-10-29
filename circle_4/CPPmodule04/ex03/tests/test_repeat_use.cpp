/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_repeat_use.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:30:59 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/08 13:31:02 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include "Character.hpp"

int main() {
    IMateriaSource* src = new MateriaSource();
    src->learnMateria(new Ice());

    ICharacter* me = new Character("me");

    AMateria* tmp = src->createMateria("ice");
    me->equip(tmp);

    ICharacter* bob = new Character("bob");

    me->use(0, *bob);
    me->use(0, *bob);

    delete bob;
    delete me;
    delete src;
    return 0;
}

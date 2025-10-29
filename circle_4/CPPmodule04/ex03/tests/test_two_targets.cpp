/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_two_targets.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:31:46 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/08 13:31:51 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include "Character.hpp"

int main() {
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
    ICharacter* eve = new Character("eve");

    me->use(0, *bob); // ice -> bob
    me->use(1, *eve); // cure -> eve

    delete eve;
    delete bob;
    delete me;
    delete src;
    return 0;
}

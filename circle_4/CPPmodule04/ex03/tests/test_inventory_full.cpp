/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_inventory_full.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:33:25 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/08 13:33:27 by rghisoiu         ###   ########.fr       */
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

    me->equip(src->createMateria("ice"));
    me->equip(src->createMateria("cure"));
    me->equip(src->createMateria("ice"));
    me->equip(src->createMateria("cure"));
    me->equip(src->createMateria("ice")); // inventar plin, ignorat

    ICharacter* bob = new Character("bob");

    me->use(0, *bob);
    me->use(1, *bob);
    me->use(2, *bob);
    me->use(3, *bob);

    delete bob;
    delete me;
    delete src;
    return 0;
}

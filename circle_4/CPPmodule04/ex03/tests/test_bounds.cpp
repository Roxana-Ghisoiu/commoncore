/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_bounds.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:13:52 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/08 13:13:54 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include "Character.hpp"
#include <iostream>

int main() {
    MateriaSource src;
    src.learnMateria(new Ice());
    src.learnMateria(new Cure());

    Character x("x");
    x.equip(src.createMateria("ice"));
    x.equip(src.createMateria("cure"));

    std::cout << "[bounds] use(-1): ";
    x.use(-1, x);
    std::cout << "[bounds] use(99): ";
    x.use(99, x);

    x.unequip(0);
    std::cout << "[bounds] use(0) after unequip: ";
    x.use(0, x);

    x.unequip(3);
    x.unequip(-2);
    x.unequip(42);

    std::cout << "[bounds] done\n";
}

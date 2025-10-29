/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_deepcopy.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:10:38 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/08 13:10:40 by rghisoiu         ###   ########.fr       */
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

    Character a("alice");
    a.equip(src.createMateria("ice"));
    a.equip(src.createMateria("cure"));

    Character b = a;
    a.unequip(0);
    std::cout << "[deepcopy] original uses slot 0: ";
    a.use(0, a);
    std::cout << "[deepcopy] copy uses slot 0: ";
    b.use(0, b);

    Character c("charlie");
    c = a;
    std::cout << "[assign] copy uses slot 1: ";
    c.use(1, c);
}

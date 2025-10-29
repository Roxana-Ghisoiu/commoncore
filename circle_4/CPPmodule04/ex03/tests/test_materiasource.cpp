/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_materiasource.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:11:37 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/08 13:11:41 by rghisoiu         ###   ########.fr       */
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

    AMateria* u = src.createMateria("unknown");
    std::cout << "[msrc] unknown type returns " << (u == 0 ? "NULL" : "not null") << "\n";
    if (u) delete u;

    AMateria* i = src.createMateria("ice");
    std::cout << "[msrc] ice type returns " << (i != 0 ? "ok" : "NULL") << "\n";
    delete i;

    AMateria* c = src.createMateria("cure");
    std::cout << "[msrc] cure type returns " << (c != 0 ? "ok" : "NULL") << "\n";
    delete c;
}

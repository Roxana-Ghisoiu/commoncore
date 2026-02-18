/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:10:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/05 15:36:32 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Intern.hpp"
#include "../inc/ShrubberyCreationForm.hpp"
#include "../inc/RobotomyRequestForm.hpp"
#include "../inc/PresidentialPardonForm.hpp"
#include <iostream>

/**
 * @file Intern.cpp
 * @brief Implementation of the Intern factory (creates concrete AForm by name).
 *
 * The Intern produces forms using a small dispatch table (name -> constructor),
 * avoiding long if/else chains. On success, it prints "Intern creates <form>" and
 * returns a newly allocated AForm*. On unknown form names, it prints an explicit
 * error message and throws UnknownFormException.
 */

namespace {
    // Plain C++98 function pointers for constructors
    static AForm* makeShrub(const std::string& target) { return new ShrubberyCreationForm(target); }
    static AForm* makeRobo(const std::string& target)  { return new RobotomyRequestForm(target); }
    static AForm* makePardon(const std::string& target){ return new PresidentialPardonForm(target); }
}

Intern::Intern() {}
Intern::Intern(const Intern& other) { (void)other; }
Intern& Intern::operator=(const Intern& other) { (void)other; return *this; }
Intern::~Intern() {}

AForm* Intern::makeForm(const std::string& name, const std::string& target) const {
    struct Entry {
        const char* key;
        AForm* (*ctor)(const std::string&);
    };

    static const Entry table[3] = {
        { "shrubbery creation",  &makeShrub  },
        { "robotomy request",    &makeRobo   },
        { "presidential pardon", &makePardon }
    };

    for (int i = 0; i < 3; ++i) {
        if (name == table[i].key) {
            AForm* f = table[i].ctor(target);
            std::cout << "Intern creates " << f->getName() << std::endl;
            return f;
        }
    }

    std::cerr << "Intern: unknown form name \"" << name << "\"" << std::endl;
    throw UnknownFormException();
}

const char* Intern::UnknownFormException::what() const throw() {
    return "Intern: unknown form name";
}
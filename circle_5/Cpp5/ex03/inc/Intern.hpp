/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:10:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/03 19:09:36 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
#define INTERN_HPP

#include <string>
#include <exception>
#include "AForm.hpp"

/**
 * @brief Intern creates concrete forms by name (factory method).
 *
 * Supported names:
 *  - "shrubbery creation"
 *  - "robotomy request"
 *  - "presidential pardon"
 *
 * makeForm returns a newly allocated AForm* or throws on unknown name.
 */
class Intern {
public:
    Intern();
    Intern(const Intern& other);
    Intern& operator=(const Intern& other);
    ~Intern();

    AForm* makeForm(const std::string& name, const std::string& target) const;

    class UnknownFormException : public std::exception {
    public:
        const char* what() const throw();
    };
};

#endif
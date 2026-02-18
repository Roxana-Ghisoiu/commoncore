/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:40:31 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/23 14:41:34 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include "AForm.hpp"
#include <fstream>


class ShrubberyCreationForm : public AForm {
public:
ShrubberyCreationForm(const std::string &target);
ShrubberyCreationForm(const ShrubberyCreationForm &other);
~ShrubberyCreationForm();
ShrubberyCreationForm &operator=(const ShrubberyCreationForm &other);


protected:
virtual void doExecute() const;


public:
class FileErrorException : public std::exception {
public: const char *what() const throw(); };
};


#endif
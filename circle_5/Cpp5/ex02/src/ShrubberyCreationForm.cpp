/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 19:05:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/03 19:28:05 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ShrubberyCreationForm.hpp"
#include <fstream>

/**
 * @brief Writes ASCII trees to <target>_shrubbery.
 */

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
: AForm("ShrubberyCreation", 145, 137, target) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other)
: AForm(other) {}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other) {
    if (this != &other) {
        AForm::operator=(other);
    }
    return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

void ShrubberyCreationForm::executeAction() const {
    std::ofstream ofs((getTarget() + "_shrubbery").c_str());
    if (!ofs) return;
    ofs << "   ccee88oo\n"
           " C8O8O8Q8PoOb o8oo\n"
           "dOB69QO8PdUOpugoO9bD\n"
           "CgggbU8OU qOp qOdoUOdcb\n"
           "    6OuU  /p u gcoUodpP\n"
           "      \\\\//  /douUP\n"
           "        \\\\////\n"
           "         |||/\\\n"
           "         |||\\/\n"
           "         |||||\n"
           "   .....//||||\\....\n";
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:51:29 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/03 19:32:44 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
: AForm("ShrubberyCreationForm", 145, 137, target) {}


ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other)
: AForm(other) {}


ShrubberyCreationForm::~ShrubberyCreationForm() {}


ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other) {
AForm::operator=(other);
return *this;
}

void ShrubberyCreationForm::doExecute() const {
    const std::string filename = this->getTarget() + "_shrubbery";
    std::ofstream ofs(filename.c_str(), std::ios::out | std::ios::trunc);
    if (!ofs) {
        throw std::runtime_error("ShrubberyCreationForm: cannot open output file");
    }

    ofs << " /\\\\\\\\\\\n"
           " /\\/////////\\\n"
           " /\\///////////\\\n"
           " /\\/////\\\\\\///\\\n"
           " /\\\\/////\\/\\\\\\\\\\//\\\\\n"
           " ||||  ||||\n"
           " ||||  ||||\n";

    ofs.close();
    if (!ofs) {
        throw std::runtime_error("ShrubberyCreationForm: write error");
    }
}
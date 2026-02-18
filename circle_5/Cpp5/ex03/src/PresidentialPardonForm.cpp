/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:54:18 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/03 19:32:22 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/PresidentialPardonForm.hpp"
#include <iostream>


PresidentialPardonForm::PresidentialPardonForm(const std::string &target)
: AForm("PresidentialPardonForm", 25, 5, target) {}


PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &other)
: AForm(other) {}


PresidentialPardonForm::~PresidentialPardonForm() {}


PresidentialPardonForm &PresidentialPardonForm::operator=(const PresidentialPardonForm &other) {
AForm::operator=(other);
return *this;
}


void PresidentialPardonForm::doExecute() const {
std::cout << getTarget() << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:52:21 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/03 19:32:33 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/RobotomyRequestForm.hpp"
#include <iostream>


RobotomyRequestForm::RobotomyRequestForm(const std::string &target)
: AForm("RobotomyRequestForm", 72, 45, target) {}


RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other)
: AForm(other) {}


RobotomyRequestForm::~RobotomyRequestForm() {}


RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &other) {
AForm::operator=(other);
return *this;
}


void RobotomyRequestForm::doExecute() const {
static bool seeded = false;
if (!seeded) { std::srand(static_cast<unsigned int>(std::time(NULL))); seeded = true; }
std::cout << "* BZZZZT * drilling noises..." << std::endl;
if (std::rand() % 2)
std::cout << getTarget() << " has been robotomized successfully!" << std::endl;
else
std::cout << "Robotomy failed for " << getTarget() << "." << std::endl;
}
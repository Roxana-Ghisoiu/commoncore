/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 19:05:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/03 19:27:45 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/RobotomyRequestForm.hpp"
#include <cstdlib>
#include <iostream>

/**
 * @brief Prints drilling noises and a 50% success/failure message.
 */

RobotomyRequestForm::RobotomyRequestForm(const std::string& target)
: AForm("RobotomyRequest", 72, 45, target) {}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& other)
: AForm(other) {}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& other) {
    if (this != &other) {
        AForm::operator=(other);
    }
    return *this;
}

RobotomyRequestForm::~RobotomyRequestForm() {}

void RobotomyRequestForm::executeAction() const {
    std::cout << "* bzzzzzz... drrrrr... *" << std::endl;
    if (std::rand() % 2)
        std::cout << getTarget() << " has been robotomized successfully." << std::endl;
    else
        std::cout << "Robotomy failed on " << getTarget() << "." << std::endl;
}
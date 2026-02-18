/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:42:17 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/23 14:42:29 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP


#include "AForm.hpp"
#include <cstdlib>
#include <ctime>


class RobotomyRequestForm : public AForm {
public:
RobotomyRequestForm(const std::string &target);
RobotomyRequestForm(const RobotomyRequestForm &other);
~RobotomyRequestForm();
RobotomyRequestForm &operator=(const RobotomyRequestForm &other);


protected:
virtual void doExecute() const;
};


#endif
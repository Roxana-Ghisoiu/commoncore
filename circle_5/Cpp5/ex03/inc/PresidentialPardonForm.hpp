/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:43:09 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/23 14:43:34 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP


#include "AForm.hpp"


class PresidentialPardonForm : public AForm {
public:
PresidentialPardonForm(const std::string &target);
PresidentialPardonForm(const PresidentialPardonForm &other);
~PresidentialPardonForm();
PresidentialPardonForm &operator=(const PresidentialPardonForm &other);


protected:
virtual void doExecute() const;
};


#endif
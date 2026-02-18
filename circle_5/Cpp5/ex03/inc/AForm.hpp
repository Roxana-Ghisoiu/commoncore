/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:37:25 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/23 14:49:18 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFORM_HPP
#define AFORM_HPP


#include <string>
#include <iostream>


class Bureaucrat;


class AForm {
private:
const std::string _name;
bool _signed;
const int _gradeToSign;
const int _gradeToExecute;
std::string _target;


AForm(); // disabled default


public:
// Canonical form (no default)
AForm(const std::string &name, int gradeToSign, int gradeToExecute, const std::string &target);
AForm(const AForm &other);
virtual ~AForm();
AForm &operator=(const AForm &other);


// Getters
const std::string &getName() const;
bool isSigned() const;
int getGradeToSign() const;
int getGradeToExecute() const;
const std::string &getTarget() const;


// Interface
void beSigned(Bureaucrat const &b);
void execute(Bureaucrat const &executor) const; // final check + calls doExecute()


protected:
virtual void doExecute() const = 0; // implemented by concrete forms


public:
// Exceptions
class GradeTooHighException : public std::exception {
public: const char *what() const throw(); };
class GradeTooLowException : public std::exception {
public: const char *what() const throw(); };
class NotSignedException : public std::exception {
public: const char *what() const throw(); };
};


std::ostream &operator<<(std::ostream &os, const AForm &f);

#endif
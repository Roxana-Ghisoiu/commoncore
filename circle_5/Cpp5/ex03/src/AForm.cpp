/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 14:40:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/03 19:29:06 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/AForm.hpp"
#include "../inc/Bureaucrat.hpp"


AForm::AForm(const std::string &name, int gradeToSign, int gradeToExecute, const std::string &target)
: _name(name), _signed(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute), _target(target) {
if (_gradeToSign < 1 || _gradeToExecute < 1) throw GradeTooHighException();
if (_gradeToSign > 150 || _gradeToExecute > 150) throw GradeTooLowException();
}


AForm::AForm(const AForm &other)
: _name(other._name), _signed(other._signed), _gradeToSign(other._gradeToSign),
_gradeToExecute(other._gradeToExecute), _target(other._target) {}


AForm::~AForm() {}


AForm &AForm::operator=(const AForm &other) {
if (this != &other) {
_signed = other._signed;
// _name, _gradeToSign, _gradeToExecute are const
_target = other._target;
}
return *this;
}


const std::string &AForm::getName() const { return _name; }
bool AForm::isSigned() const { return _signed; }
int AForm::getGradeToSign() const { return _gradeToSign; }
int AForm::getGradeToExecute() const { return _gradeToExecute; }
const std::string &AForm::getTarget() const { return _target; }


void AForm::beSigned(Bureaucrat const &b) {
if (b.getGrade() > _gradeToSign) throw GradeTooLowException();
_signed = true;
}


void AForm::execute(Bureaucrat const &executor) const {
if (!_signed) throw NotSignedException();
if (executor.getGrade() > _gradeToExecute) throw GradeTooLowException();
this->doExecute();
}


const char *AForm::GradeTooHighException::what() const throw() { return "form grade too high"; }
const char *AForm::GradeTooLowException::what() const throw() { return "form grade too low"; }
const char *AForm::NotSignedException::what() const throw() { return "form not signed"; }


std::ostream &operator<<(std::ostream &os, const AForm &f) {
os << "Form '" << f.getName() << "' [signed=" << (f.isSigned() ? "yes" : "no")
<< ", signGrade=" << f.getGradeToSign()
<< ", execGrade=" << f.getGradeToExecute()
<< ", target='" << f.getTarget() << "']";
return os;
}
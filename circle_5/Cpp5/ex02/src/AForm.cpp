/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 19:00:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/03 19:24:45 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/AForm.hpp"
#include "../inc/Bureaucrat.hpp"

/**
 * @brief Implementation for AForm: validation, signing, execution template.
 */

void AForm::assertGradeInRange(int g) const {
    if (g < kMaxGrade) throw GradeTooHighException();
    if (g > kMinGrade) throw GradeTooLowException();
}

AForm::AForm()
: _name("Untitled"), _signed(false), _gradeToSign(150), _gradeToExecute(150), _target("default") {
    assertGradeInRange(_gradeToSign);
    assertGradeInRange(_gradeToExecute);
}

AForm::AForm(const std::string& name, int gradeToSign, int gradeToExecute, const std::string& target)
: _name(name), _signed(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute), _target(target) {
    assertGradeInRange(_gradeToSign);
    assertGradeInRange(_gradeToExecute);
}

AForm::AForm(const AForm& other)
: _name(other._name), _signed(other._signed),
  _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute),
  _target(other._target) {
    assertGradeInRange(_gradeToSign);
    assertGradeInRange(_gradeToExecute);
}

AForm& AForm::operator=(const AForm& other) {
    if (this != &other) {
        _signed  = other._signed;
        _target  = other._target;
    }
    return *this;
}

AForm::~AForm() {}

const std::string& AForm::getName() const { return _name; }
bool               AForm::isSigned() const { return _signed; }
int                AForm::getGradeToSign() const { return _gradeToSign; }
int                AForm::getGradeToExecute() const { return _gradeToExecute; }
const std::string& AForm::getTarget() const { return _target; }

void AForm::beSigned(const Bureaucrat& b) {
    if (b.getGrade() <= _gradeToSign) _signed = true;
    else throw GradeTooLowException();
}

void AForm::execute(const Bureaucrat& executor) const {
    if (!_signed) throw FormNotSignedException();
    if (executor.getGrade() > _gradeToExecute) throw GradeTooLowException();
    executeAction();
}

const char* AForm::GradeTooHighException::what() const throw() { return "Form: grade too high (minimum is 1)"; }
const char* AForm::GradeTooLowException::what() const throw()  { return "Form: grade too low (maximum is 150)"; }
const char* AForm::FormNotSignedException::what() const throw(){ return "Form: not signed"; }

std::ostream& operator<<(std::ostream& os, const AForm& f) {
    os << "Form \"" << f.getName() << "\""
       << " [signed: " << (f.isSigned() ? "yes" : "no")
       << ", gradeToSign: " << f.getGradeToSign()
       << ", gradeToExecute: " << f.getGradeToExecute()
       << ", target: " << f.getTarget()
       << "].";
    return os;
}
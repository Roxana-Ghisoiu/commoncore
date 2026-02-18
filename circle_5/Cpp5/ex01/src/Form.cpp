/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:50:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/05 12:31:38 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Form.hpp"
#include "../inc/Bureaucrat.hpp"


/**
 * @brief Implementation file for Form.
 *
 * Validates grade constraints, exposes getters, printing, and
 * implements beSigned() that checks a Bureaucrat's grade against
 * the required grade to sign.
 */

void Form::assertGradeInRange(int g) const {
    if (g < kMaxGrade)
        throw GradeTooHighException();
    if (g > kMinGrade)
        throw GradeTooLowException();
}

Form::Form()
: _name("Untitled"), _signed(false), _gradeToSign(150), _gradeToExecute(150) {
    assertGradeInRange(_gradeToSign);
    assertGradeInRange(_gradeToExecute);
}

Form::Form(const std::string& name, int gradeToSign, int gradeToExecute)
: _name(name), _signed(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute) {
    assertGradeInRange(_gradeToSign);
    assertGradeInRange(_gradeToExecute);
}

Form::Form(const Form& other)
: _name(other._name), _signed(other._signed),
  _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute) {
    assertGradeInRange(_gradeToSign);
    assertGradeInRange(_gradeToExecute);
}

Form& Form::operator=(const Form& other) {
    if (this != &other) {
        _signed = other._signed;
    }
    return *this;
}

Form::~Form() {}

const std::string& Form::getName() const { return _name; }
bool               Form::isSigned() const { return _signed; }
int                Form::getGradeToSign() const { return _gradeToSign; }
int                Form::getGradeToExecute() const { return _gradeToExecute; }

void Form::beSigned(const Bureaucrat& b) {
    if (b.getGrade() <= _gradeToSign) {
        _signed = true;
    } else {
        throw GradeTooLowException();
    }
}

const char* Form::GradeTooHighException::what() const throw() {
    return "Form: grade too high (minimum is 1)";
}

const char* Form::GradeTooLowException::what() const throw() {
    return "Form: grade too low (maximum is 150)";
}

std::ostream& operator<<(std::ostream& os, const Form& f) {
    os << "Form \"" << f.getName() << "\""
       << " [signed: " << (f.isSigned() ? "yes" : "no")
       << ", gradeToSign: " << f.getGradeToSign()
       << ", gradeToExecute: " << f.getGradeToExecute()
       << "].";
    return os;
}
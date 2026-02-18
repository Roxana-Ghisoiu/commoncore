/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:34:42 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/03 19:23:15 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Form.hpp"
#include "../inc/Bureaucrat.hpp"

/**
 * @brief Implementation file for Bureaucrat.
 *
 * Provides construction, grade checks, modifiers, I/O operator, and
 * the signForm() behavior which delegates to Form::beSigned().
 */

void Bureaucrat::assertGradeInRange(int g) const {
    if (g < kMaxGrade)
        throw GradeTooHighException();
    if (g > kMinGrade)
        throw GradeTooLowException();
}

Bureaucrat::Bureaucrat()
: _name("Unnamed"), _grade(150) {
    assertGradeInRange(_grade);
}

Bureaucrat::Bureaucrat(const std::string& name, int grade)
: _name(name), _grade(grade) {
    assertGradeInRange(_grade);
}

Bureaucrat::Bureaucrat(const Bureaucrat& other)
: _name(other._name), _grade(other._grade) {
    assertGradeInRange(_grade);
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other) {
    if (this != &other) {
        _grade = other._grade;
    }
    return *this;
}

Bureaucrat::~Bureaucrat() {}

const std::string& Bureaucrat::getName() const { return _name; }
int                Bureaucrat::getGrade() const { return _grade; }

void Bureaucrat::incrementGrade() {
    assertGradeInRange(_grade - 1);
    --_grade;
}

void Bureaucrat::decrementGrade() {
    assertGradeInRange(_grade + 1);
    ++_grade;
}

void Bureaucrat::signForm(Form& form) {
    try {
        form.beSigned(*this);
        std::cout << _name << " signed " << form.getName() << std::endl;
    } catch (const std::exception& e) {
        std::cout << _name << " couldn't sign " << form.getName()
                  << " because " << e.what() << std::endl;
    }
}

const char* Bureaucrat::GradeTooHighException::what() const throw() {
    return "Bureaucrat: grade too high (minimum is 1)";
}

const char* Bureaucrat::GradeTooLowException::what() const throw() {
    return "Bureaucrat: grade too low (maximum is 150)";
}

std::ostream& operator<<(std::ostream& os, const Bureaucrat& b) {
    os << b.getName() << ", bureaucrat grade " << b.getGrade() << '.';
    return os;
}
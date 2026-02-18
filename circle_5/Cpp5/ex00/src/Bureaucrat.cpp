/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:34:42 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/23 13:03:36 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

/**
 * @brief Implementation of the Bureaucrat class.
 *
 * This class represents a bureaucrat with a constant name and a grade ranging
 * from 1 (highest rank) to 150 (lowest rank). It provides functions to get
 * the name and grade, increment or decrement the grade while checking bounds,
 * and throws exceptions if the grade goes out of range.
 */

// ========================== Utils ==========================

void Bureaucrat::assertGradeInRange(int g) const {
    if (g < kMaxGrade)
        throw GradeTooHighException();
    if (g > kMinGrade)
        throw GradeTooLowException();
}

// =================== Orthodox Canonical Form ===================

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
        _grade = other._grade; // _name is const and cannot be reassigned
    }
    return *this;
}

Bureaucrat::~Bureaucrat() {}

// ========================= Getters =========================

const std::string& Bureaucrat::getName() const { return _name; }
int                Bureaucrat::getGrade() const { return _grade; }

// ====================== Grade modifiers ======================

void Bureaucrat::incrementGrade() {
    assertGradeInRange(_grade - 1);
    --_grade;
}

void Bureaucrat::decrementGrade() {
    assertGradeInRange(_grade + 1);
    ++_grade;
}

// ========================= Exceptions =========================

const char* Bureaucrat::GradeTooHighException::what() const throw() {
    return "Bureaucrat: grade too high (minimum is 1)";
}

const char* Bureaucrat::GradeTooLowException::what() const throw() {
    return "Bureaucrat: grade too low (maximum is 150)";
}

// ===================== Stream insertion =====================

std::ostream& operator<<(std::ostream& os, const Bureaucrat& b) {
    os << b.getName() << ", bureaucrat grade " << b.getGrade() << '.';
    return os;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:34:29 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/03 18:58:49 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <exception>
#include <string>
#include <iostream>

/**
 * @brief Bureaucrat with constant name and grade in [1..150].
 *
 * Provides grade modification, signing of forms, and execution of forms.
 * Throws GradeTooHighException/GradeTooLowException when out of bounds.
 */
class AForm; // forward

class Bureaucrat {
public:
    Bureaucrat();
    Bureaucrat(const std::string& name, int grade);
    Bureaucrat(const Bureaucrat& other);
    Bureaucrat& operator=(const Bureaucrat& other);
    ~Bureaucrat();

    const std::string& getName() const;
    int                getGrade() const;

    void incrementGrade();
    void decrementGrade();

    void signForm(AForm& form) const;
    void executeForm(const AForm& form) const;

    class GradeTooHighException : public std::exception {
    public:
        const char* what() const throw();
    };

    class GradeTooLowException : public std::exception {
    public:
        const char* what() const throw();
    };

private:
    const std::string _name;
    int               _grade;

    enum { kMaxGrade = 1, kMinGrade = 150 };

    void assertGradeInRange(int g) const;
};

std::ostream& operator<<(std::ostream& os, const Bureaucrat& b);

#endif
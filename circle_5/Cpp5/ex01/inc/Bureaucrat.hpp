/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:17:54 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/03 18:18:11 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <exception>
#include <string>
#include <iostream>

/**
 * @brief Bureaucrat represents a bureaucrat with a constant name and a grade.
 *
 * Grade is in range [1..150], where 1 is the highest rank and 150 the lowest.
 * Construction and grade changes outside the valid range throw exceptions.
 * In ex01, Bureaucrat can attempt to sign a Form via signForm().
 */
class Form; // forward declaration

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

    void signForm(Form& form);

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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:50:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/03 18:18:48 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
#define FORM_HPP

#include <exception>
#include <string>
#include <iostream>

/**
 * @brief Form represents a form that can be signed and executed.
 *
 * Attributes:
 *  - constant name
 *  - signed status (initially false)
 *  - constant grade required to sign
 *  - constant grade required to execute
 *
 * Grades obey the same rules as Bureaucrat: 1 is highest, 150 lowest.
 * Throws GradeTooHighException / GradeTooLowException on invalid grades.
 * The beSigned() member sets the form as signed if the bureaucrat's grade
 * is high enough (numerically <= required grade), otherwise throws.
 */
class Bureaucrat; // forward declaration

class Form {
public:
    Form();
    Form(const std::string& name, int gradeToSign, int gradeToExecute);
    Form(const Form& other);
    Form& operator=(const Form& other);
    ~Form();

    const std::string& getName() const;
    bool               isSigned() const;
    int                getGradeToSign() const;
    int                getGradeToExecute() const;

    void beSigned(const Bureaucrat& b);

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
    bool              _signed;
    const int         _gradeToSign;
    const int         _gradeToExecute;

    enum { kMaxGrade = 1, kMinGrade = 150 };

    void assertGradeInRange(int g) const;
};

std::ostream& operator<<(std::ostream& os, const Form& f);

#endif
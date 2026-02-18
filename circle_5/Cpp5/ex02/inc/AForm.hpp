/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 19:00:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/03 18:41:36 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFORM_HPP
#define AFORM_HPP

#include <exception>
#include <string>
#include <iostream>

/**
 * @brief Abstract base form with private attributes and target.
 *
 * Attributes (all private, target included):
 *  - const std::string _name
 *  - bool _signed
 *  - const int _gradeToSign
 *  - const int _gradeToExecute
 *  - std::string _target
 *
 * Provides getters, beSigned(bureaucrat), and a template execute() that
 * checks signed status and executor grade, then calls executeAction().
 */
class Bureaucrat; // forward

class AForm {
public:
    AForm();
    AForm(const std::string& name, int gradeToSign, int gradeToExecute, const std::string& target);
    AForm(const AForm& other);
    AForm& operator=(const AForm& other);
    virtual ~AForm();

    const std::string& getName() const;
    bool               isSigned() const;
    int                getGradeToSign() const;
    int                getGradeToExecute() const;
    const std::string& getTarget() const;

    void beSigned(const Bureaucrat& b);

    void execute(const Bureaucrat& executor) const;

    class GradeTooHighException : public std::exception {
    public:
        const char* what() const throw();
    };
    class GradeTooLowException : public std::exception {
    public:
        const char* what() const throw();
    };
    class FormNotSignedException : public std::exception {
    public:
        const char* what() const throw();
    };

protected:
    virtual void executeAction() const = 0;

private:
    const std::string _name;
    bool              _signed;
    const int         _gradeToSign;
    const int         _gradeToExecute;
    std::string       _target;

    enum { kMaxGrade = 1, kMinGrade = 150 };

    void assertGradeInRange(int g) const;
};

std::ostream& operator<<(std::ostream& os, const AForm& f);

#endif
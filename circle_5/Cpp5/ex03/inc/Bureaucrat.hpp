/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:34:29 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/26 13:41:53 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP


#include <string>
#include <iostream>


class AForm; // forward declaration


class Bureaucrat {
private:
const std::string _name;
int _grade; // 1 (highest) .. 150 (lowest)


public:
// Orthodox Canonical Form
Bureaucrat(const std::string &name = "Bob", int grade = 150);
Bureaucrat(const Bureaucrat &other);
~Bureaucrat();
Bureaucrat &operator=(const Bureaucrat &other);


// Getters
const std::string &getName() const;
int getGrade() const;


// Grade manipulation
void incrementGrade(); // --grade (higher)
void decrementGrade(); // ++grade (lower)


// Form interactions
void signForm(AForm &form) const;
void executeForm(AForm const &form) const;


// Exceptions
class GradeTooHighException : public std::exception {
public: const char *what() const throw(); };
class GradeTooLowException : public std::exception {
public: const char *what() const throw(); };
};


std::ostream &operator<<(std::ostream &os, const Bureaucrat &b);

#endif
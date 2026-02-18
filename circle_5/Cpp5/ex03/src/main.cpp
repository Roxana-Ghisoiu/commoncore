/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 20:12:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/03 19:32:07 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Bureaucrat.hpp"
#include "../inc/Intern.hpp"
#include "../inc/AForm.hpp"
#include "../inc/ShrubberyCreationForm.hpp"
#include "../inc/RobotomyRequestForm.hpp"
#include "../inc/PresidentialPardonForm.hpp"
#include <cstdlib>
#include <ctime>

/**
 * @brief Tests Intern::makeForm and full sign/execute flow.
 */

int main() {
    std::srand(static_cast<unsigned int>(std::time(0)));

    Intern someRandomIntern;
    Bureaucrat boss("Boss", 1);
    Bureaucrat mid("Mid", 45);
    Bureaucrat low("Low", 150);

    try {
        AForm* f1 = someRandomIntern.makeForm("shrubbery creation", "garden");
        AForm* f2 = someRandomIntern.makeForm("robotomy request", "Bender");
        AForm* f3 = someRandomIntern.makeForm("presidential pardon", "Arthur Dent");

        std::cout << *f1 << std::endl;
        std::cout << *f2 << std::endl;
        std::cout << *f3 << std::endl;

        low.signForm(*f1);
        low.executeForm(*f1);

        mid.signForm(*f2);
        mid.executeForm(*f2);

        boss.signForm(*f3);
        boss.executeForm(*f3);

        boss.executeForm(*f1);

        delete f1;
        delete f2;
        delete f3;
    } catch (const std::exception& e) {
        std::cerr << "Creation/Execution error: " << e.what() << std::endl;
    }

    try {
        AForm* bad = someRandomIntern.makeForm("unknown thing", "nowhere");
        delete bad;
    } catch (const std::exception& e) {
        std::cerr << "Expected failure: " << e.what() << std::endl;
    }

    return 0;
}
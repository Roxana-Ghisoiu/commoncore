/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 19:10:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/05 14:47:47 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/AForm.hpp"
#include "../inc/Bureaucrat.hpp"
#include "../inc/ShrubberyCreationForm.hpp"
#include "../inc/RobotomyRequestForm.hpp"
#include "../inc/PresidentialPardonForm.hpp"
#include <cstdlib>
#include <ctime>
#include <fstream>   // <-- needed for std::ifstream

int main() {
    std::srand(static_cast<unsigned int>(std::time(0)));

    Bureaucrat boss("Boss", 1);
    Bureaucrat mid("Mid", 45);
    Bureaucrat low("Low", 150);

    ShrubberyCreationForm shrub("home");
    RobotomyRequestForm   robo("Bender");
    PresidentialPardonForm prez("Arthur Dent");
    ShrubberyCreationForm shrub2("garden"); // for unsigned-exec test

    std::cout << boss << std::endl;
    std::cout << mid  << std::endl;
    std::cout << low  << std::endl;

    std::cout << shrub << std::endl;
    std::cout << robo  << std::endl;
    std::cout << prez  << std::endl;

    // --- ShrubberyCreationForm (sign 145, exec 137) ---
    low.signForm(shrub);        // fail: 150 > 145
    low.executeForm(shrub);     // fail: still unsigned
    boss.signForm(shrub);       // success
    boss.executeForm(shrub);    // success: creates "home_shrubbery"

    // print the shrub file to stdout
    {
        std::ifstream in("home_shrubbery");
        if (in) {
            std::cout << in.rdbuf();
        } else {
            std::cout << "[warn] could not open home_shrubbery to display\n";
        }
    }

    // --- RobotomyRequestForm (sign 72, exec 45) ---
    mid.signForm(robo);         // success: 45 <= 72
    mid.executeForm(robo);      // success: 45 <= 45 (random success/fail message)
    mid.executeForm(robo);      // run again to showcase ~50% randomness

    // --- PresidentialPardonForm (sign 25, exec 5) ---
    mid.signForm(prez);         // fail: 45 > 25
    boss.signForm(prez);        // success
    mid.executeForm(prez);      // fail: 45 > 5
    boss.executeForm(prez);     // success: prints the pardon message

    // --- Unsigned execute rejection (explicit) ---
    boss.executeForm(shrub2);   // fail: not signed

    return 0;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:55:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/05 14:59:23 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Form.hpp"
#include "../inc/Bureaucrat.hpp"

/**
 * @brief Minimal tests for Form and Bureaucrat interaction.
 *
 * Covers:
 *  - valid/invalid form grade construction
 *  - signing success and failure paths
 *  - operator<< outputs
 */

int main() {
    try {
        Form f1("LeaveRequest", 10, 20);
        std::cout << f1 << std::endl;

        Bureaucrat boss("Boss", 5);
        Bureaucrat intern("Intern", 120);

        std::cout << boss << std::endl;
        std::cout << intern << std::endl;

        boss.signForm(f1);
        std::cout << f1 << std::endl;

        Form f2("TopSecret", 3, 5);
        std::cout << f2 << std::endl;

        intern.signForm(f2);
        std::cout << f2 << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Construction error: " << e.what() << std::endl;
    }

    try {
        Form bad("Bad", 0, 10);
        std::cout << bad << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Expected invalid form: " << e.what() << std::endl;
    }

    try {
        Form bad2("Bad2", 10, 151);
        std::cout << bad2 << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Expected invalid form: " << e.what() << std::endl;
    }

    return 0;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:48:58 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/07 16:52:11 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Base.hpp"


/**
 * @brief Tests generate(), identify(Base*), and identify(Base&).
 */
int main() {
    Base* ptr = generate();
    std::cout << "Identify by pointer: ";
    identify(ptr);
    std::cout << "Identify by reference: ";
    identify(*ptr);
    delete ptr;

    std::cout << "--- Testing nullptr ---" << std::endl;
    Base* nullPtr = NULL;
    std::cout << "Identify nullptr: ";
    identify(nullPtr);

    std::cout << "--- Testing all types ---" << std::endl;

    Base* a = new A();
    Base* b = new B();
    Base* c = new C();

    std::cout << "A by pointer: ";
    identify(a);
    std::cout << "A by reference: ";
    identify(*a);

    std::cout << "B by pointer: ";
    identify(b);
    std::cout << "B by reference: ";
    identify(*b);

    std::cout << "C by pointer: ";
    identify(c);
    std::cout << "C by reference: ";
    identify(*c);

    delete a;
    delete b;
    delete c;

    return 0;
}
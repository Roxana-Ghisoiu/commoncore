/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:48:13 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/07 14:48:40 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Base.hpp"

Base::~Base() {}

static void seed_once() {
    static bool seeded = false;
    if (!seeded) { std::srand(static_cast<unsigned int>(std::time(0))); seeded = true; }
}

Base* generate(void) {
    seed_once();
    int r = std::rand() % 3;
    if (r == 0) return new A();
    if (r == 1) return new B();
    return new C();
}

void identify(Base* p) {
    if (!p) { std::cout << "Unknown" << std::endl; return; }
    if (dynamic_cast<A*>(p)) { std::cout << "A" << std::endl; return; }
    if (dynamic_cast<B*>(p)) { std::cout << "B" << std::endl; return; }
    if (dynamic_cast<C*>(p)) { std::cout << "C" << std::endl; return; }
    std::cout << "Unknown" << std::endl;
}

void identify(Base& p) {
    try { (void)dynamic_cast<A&>(p); std::cout << "A" << std::endl; return; } catch (...) {}
    try { (void)dynamic_cast<B&>(p); std::cout << "B" << std::endl; return; } catch (...) {}
    try { (void)dynamic_cast<C&>(p); std::cout << "C" << std::endl; return; } catch (...) {}
    std::cout << "Unknown" << std::endl;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:21:38 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/09 12:34:28 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "ClapTrap.hpp"

// Mic utilitar ca să marcheze secțiunile testelor
static void section(const std::string& title) {
    std::cout << "\n=== " << title << " ===\n";
}

int main() {
    // Conform subiectului: HP=10, EN=10, AD=0 la start
    section("Constructors");
    ClapTrap a("Alpha");
    ClapTrap b("Beta");

    // 1) Attack consuma 1 energie, dar AD=0 (doar mesajul conteaza la ex00)
    section("Attack drains energy");
    for (int i = 0; i < 3; ++i) {
        a.attack("TargetX");
    }

    // 2) Repair consuma 1 energie si creste HP cu amount
    //    (daca ai un 'max HP', mentioneaza in README — subiectul nu impune max)
    section("Repair consumes energy and heals");
    b.takeDamage(4);         // HP: 10 -> 6
    b.beRepaired(3);         // HP: 6 -> 9, EN: 10 -> 9

    // 3) Nu poate ataca/repara cand energia ajunge la 0
    section("Cannot act at EN=0");
    ClapTrap e("Exhausted"); // EN=10
    for (int i = 0; i < 10; ++i) e.attack("Dummy"); // scade EN la 0
    e.attack("Dummy");       // trebuie sa esueze (EN=0)
    e.beRepaired(1);         // trebuie sa esueze (EN=0)

    // 4) Damage mare -> HP ajunge la 0; nu mai poate actiona
    section("Cannot act at HP=0 (KO)");
    ClapTrap k("KO");
    k.takeDamage(15);        // HP: 10 -> 0 (clamp la 0)
    k.attack("Anyone");      // trebuie sa esueze (HP=0)
    k.beRepaired(5);         // trebuie sa esueze (HP=0)

    // 5) Secventa mixta pentru loguri clare
    section("Mixed scenario");
    ClapTrap m("Mix");
    m.attack("Dummy");       // EN: 9
    m.takeDamage(5);         // HP: 5
    m.beRepaired(4);         // HP: 9, EN: 8
    m.attack("Dummy");       // EN: 7
    m.takeDamage(20);        // HP: 0
    m.attack("Dummy");       // fail: HP=0
    m.beRepaired(2);         // fail: HP=0

    std::cout << "\n(All tests executed — verify messages match the rules.)\n";
    return 0;
}
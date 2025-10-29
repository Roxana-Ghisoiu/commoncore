/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:22:48 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/09 13:22:52 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "FragTrap.hpp"  // include your headers as named in your project

static void section(const char* title) {
    std::cout << "\n=== " << title << " ===\n";
}

int main() {
    // 1) Construction/Destruction chaining + initial actions
    section("Constructor/Destructor order");
    {
        FragTrap f("Temp");
        f.highFivesGuys();
        f.attack("Dummy");       // EN: 100 -> 99, AD=30 expected
        f.beRepaired(5);         // HP: 100 -> 105 (unless you clamp; subject doesn't require a max)
    } // here you should see: "FragTrap destroyed" then "ClapTrap destroyed"

    // 2) Energy drains to 0, then actions are blocked
    section("Energy = 0 blocks actions");
    {
        FragTrap e("Exhaust");
        for (int i = 0; i < 100; ++i) e.attack("Trainer"); // EN: 100 -> 0
        e.attack("Trainer");        // must fail (EN=0)
        e.beRepaired(1);            // must fail (EN=0)
        e.highFivesGuys();          // still prints (no state change)
    }

    // 3) HP to 0 blocks actions
    section("HP = 0 blocks actions");
    {
        FragTrap k("KO");
        k.takeDamage(100);          // HP: 100 -> 0
        k.attack("Anyone");         // must fail (HP=0)
        k.beRepaired(10);           // must fail (HP=0)
        k.takeDamage(50);           // should not go negative; keep messaging consistent
    }

    // 4) Multiple instances behave independently
    section("Multiple instances independence");
    {
        FragTrap a("Alpha");
        FragTrap b("Beta");
        a.attack("Target");         // EN Alpha: 99
        b.attack("Target");         // EN Beta : 99
        a.takeDamage(25);           // HP Alpha: 75
        b.beRepaired(10);           // HP Beta : 110 (or clamp if you chose to)
        a.highFivesGuys();
        b.highFivesGuys();
    }

    // 5) Optional: copy constructor / assignment semantics
    section("Copy constructor and assignment (optional)");
    {
        FragTrap base("Base");
        base.attack("T1");          // EN: 99
        base.takeDamage(10);        // HP: 90

        FragTrap copyCtor(base);    // constructed as copy
        copyCtor.attack("T2");      // should act independently of 'base'

        FragTrap copyAssign("Placeholder");
        copyAssign = base;          // assigned as copy
        copyAssign.beRepaired(5);   // should act independently of 'base'
    }

    std::cout << "\n(All tests executed.)\n";
    return 0;
}
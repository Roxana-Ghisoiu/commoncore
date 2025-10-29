/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:41:10 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/09 13:41:24 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "DiamondTrap.hpp"  // adjust includes to your filenames

static void section(const char* title) {
    std::cout << "\n=== " << title << " ===\n";
}

int main() {
    // 1) Construction chain + whoAmI + ability methods
    section("Constructor chain + whoAmI + abilities");
    {
        DiamondTrap d("Diana");
        // Expect: ClapTrap constructed (name: Diana_clap_name)
        //         ScavTrap constructed
        //         FragTrap constructed
        //         DiamondTrap constructed
        d.whoAmI();            // must print: DiamondTrap name + ClapTrap name
        d.attack("Dummy");     // must use ScavTrap::attack (costs 1 EN, deals 30 dmg)
        d.highFivesGuys();     // FragTrap special (just prints)
        d.guardGate();         // ScavTrap special (just prints)
    }   // Expect reverse destruction: DiamondTrap -> FragTrap -> ScavTrap -> ClapTrap

    // 2) Name rule: ClapTrap::name is param + "_clap_name"
    section("Name rule: ClapTrap::name = <param>_clap_name");
    {
        DiamondTrap x("Shiny");
        x.whoAmI();            // should print: DiamondTrap name: Shiny | ClapTrap name: Shiny_clap_name
    }

    // 3) Energy exhaustion (EN starts from ScavTrap = 50). After 50 attacks, EN must be 0.
    section("Energy exhaustion (EN from ScavTrap = 50)");
    {
        DiamondTrap e("NoEnergy");
        for (int i = 0; i < 50; ++i) e.attack("Trainer");   // EN: 50 -> 0
        e.attack("Trainer");                                // must fail (no energy)
        e.beRepaired(1);                                    // must fail (no energy)
        e.whoAmI();                                         // still prints names (no state change)
    }

    // 4) HP exhaustion (HP from FragTrap = 100). At HP=0, no attack/repair.
    section("HP exhaustion (HP from FragTrap = 100)");
    {
        DiamondTrap k("NoHP");
        k.takeDamage(100);   // HP: 100 -> 0
        k.attack("Anyone");  // must fail (no HP)
        k.beRepaired(5);     // must fail (no HP)
        k.takeDamage(50);    // must not go negative; keep message consistent
        k.whoAmI();          // names still print
    }

    // 5) Copy constructor + copy assignment: copies act independently
    section("Copy constructor + copy assignment independence");
    {
        DiamondTrap src("Source");
        src.attack("T1");       // EN: 49
        src.takeDamage(30);     // HP: 70

        DiamondTrap cpy(src);   // copy-constructed
        cpy.attack("T2");       // EN for 'cpy' changes, src remains with its own state
        cpy.whoAmI();

        DiamondTrap asg("Placeholder");
        asg = src;              // copy-assigned
        asg.beRepaired(10);     // affects 'asg' only
        asg.whoAmI();
    }

    // 6) Single ClapTrap base (virtual base): construct two, observe exactly one ClapTrap construction per DiamondTrap
    section("Single ClapTrap base check (visual)"); 
    {
        DiamondTrap a("A");
        DiamondTrap b("B");
        // Visually ensure for each DiamondTrap:
        //   one ClapTrap constructed, one ScavTrap constructed, one FragTrap constructed
        //   (i.e., no duplicate ClapTrap construction lines)
        a.attack("Dummy");
        b.attack("Dummy");
    }

    std::cout << "\n(All DiamondTrap tests executed.)\n";
    return 0;
}
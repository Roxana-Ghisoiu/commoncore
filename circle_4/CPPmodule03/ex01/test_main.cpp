/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:52:42 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/09 12:52:54 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"
#include <iostream>

int main() {
    std::cout << "=== Constructor/Destructor test ===" << std::endl;
    {
        ScavTrap tmp("Temporary");
        tmp.guardGate();
    } // aici se vede ordinea destructorilor
    
    std::cout << "\n=== HP=0 edge case ===" << std::endl;
    ScavTrap edge("Edge");
    edge.takeDamage(100);
    edge.attack("Dummy");     // should fail (HP=0)
    edge.beRepaired(10);      // should fail (HP=0)
    edge.takeDamage(50);      // still HP=0, no negative
    
    std::cout << "\n=== Two ScavTraps ===" << std::endl;
    ScavTrap one("One");
    ScavTrap two("Two");
    one.attack("Target");
    two.attack("Target");
    
    std::cout << "\n(All tests executed.)" << std::endl;
    return 0;
}
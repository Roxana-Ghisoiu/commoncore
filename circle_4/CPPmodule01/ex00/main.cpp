/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:23:46 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/01 15:17:00 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

/**
 * @brief Entry point of the program.
 * Demonstrates the creation of Zombies both on the heap and on the stack.
 * - Uses newZombie() to create a Zombie on the heap.
 * - Uses randomChump() to create a Zombie on the stack.
 *
 * @return int Exit status code.
 */
int main(void)
{
    // Create a Zombie on the heap using newZombie
    Zombie* heapZombie = newZombie("Foo");
    heapZombie->announce();

    // Delete heapZombie manually (important to avoid memory leaks)
    delete heapZombie;

    // Create a Zombie on the stack using randomChump
    randomChump("Foo");

    return 0;
}
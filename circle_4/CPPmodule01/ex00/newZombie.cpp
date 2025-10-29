/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newZombie.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:21:36 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/01 14:22:23 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

/**
 * @brief Creates a new Zombie on the heap.
 *
 * Allocates a Zombie object using the `new` operator, 
 * initializes it with the given name, and returns a pointer.
 *
 * @param name The name of the Zombie.
 * @return Zombie* A pointer to the newly created Zombie.
 */
Zombie* newZombie(std::string name)
{
    return new Zombie(name);
}

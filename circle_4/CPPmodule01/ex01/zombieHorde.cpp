/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:07:36 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/01 16:58:50 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

/**
 * @file zombieHorde.cpp
 * @brief Implements the zombieHorde function.
 *
 * This file defines the function zombieHorde(), which:
 * - Allocates N Zombies in a single memory block using new[].
 * - Initializes each Zombie with the given name using setName().
 * - Returns a pointer to the first Zombie in the horde.
 * - Returns NULL if N <= 0.
 */
Zombie* zombieHorde(int N, const std::string& name) {
    if (N <= 0)
        return NULL;

    Zombie* horde = new Zombie[N];
    for (int i = 0; i < N; ++i)
        horde[i].setName(name);
    return horde;
}

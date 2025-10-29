/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 16:08:26 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/08 16:35:25 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

/**
 * @brief Entry point of the Zombie Horde program.
 *
 * This function demonstrates the creation of a horde of Zombies
 * using the zombieHorde() function. It allocates N Zombies on the
 * heap in a single allocation, makes each Zombie announce itself,
 * and then deallocates the entire horde using delete[] to prevent
 * memory leaks.
 *
 * @return int Exit status code (0 on success, 1 on error).
 */
int main() {
    int N = 5;
    Zombie* horde = zombieHorde(N, "Foo");
    if (!horde)
        return 1;

    for (int i = 0; i < N; ++i)
        horde[i].announce();

    delete[] horde;
    return 0;
}

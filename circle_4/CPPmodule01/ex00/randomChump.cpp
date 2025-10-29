/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomChump.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:27:34 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/01 14:22:54 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

/**
 * @brief Creates a Zombie on the stack and makes it announce itself.
 *
 * This function creates a local Zombie object. The Zombie announces
 * itself immediately, and then the object is automatically destroyed 
 * when the function scope ends.
 *
 * @param name The name of the Zombie.
 */
void randomChump(std::string name)
{
    Zombie zombie(name);
    zombie.announce();
}
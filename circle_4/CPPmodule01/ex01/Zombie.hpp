/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:58:39 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/01 16:04:16 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <iostream>
#include <string>
/**
 * @file Zombie.hpp
 * @brief Declares the Zombie class and the zombieHorde function.
 *
 * This header file defines the Zombie class, which represents a simple
 * Zombie with a name that can announce itself. It also declares the
 * zombieHorde() function, which creates an array of Zombies in a single
 * allocation.
 *
 * Contents:
 * - Zombie class:
 *   - Private attribute: _name
 *   - Constructors (default and with name)
 *   - Destructor
 *   - setName() to assign the Zombie's name
 *   - announce() to make the Zombie print its message
 * - Function prototype: Zombie* zombieHorde(int N, const std::string& name);
 */

class Zombie
{
    private:
    std::string _name;

    public:
        Zombie();
        Zombie(const std::string& name);
        ~Zombie();

        void setName(const std::string& name);
        void announce(void) const;
};

Zombie* zombieHorde( int N, const std::string& name );

#endif
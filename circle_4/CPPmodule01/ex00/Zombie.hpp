/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:41:07 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/01 14:04:45 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <iostream>

/**
 * @class Zombie
 * @brief Represents a Zombie with a name that can announce itself.
 */
class Zombie {
    private:
        std::string _name; ///< Name of the Zombie

    public:
        Zombie(const std::string& name);
        ~Zombie();
        void announce(void) const;
};

Zombie* newZombie(std::string name);
void randomChump(std::string name);

#endif
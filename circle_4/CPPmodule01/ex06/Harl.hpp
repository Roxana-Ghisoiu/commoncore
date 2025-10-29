/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:35:14 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/02 14:37:51 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_HPP
# define HARL_HPP

#include <iostream>
#include <string>

/** @brief Harl log-level filter: prints messages from a selected level and above.
 *
 * Levels (in order): DEBUG < INFO < WARNING < ERROR.
 * The filter(level) method prints all messages from `level` upwards.
 */
class   Harl
{
    private:
        void    debug();
        void    info();
        void    warning();
        void    error();

    public:
        Harl();
        ~Harl();
        void    filter(const std::string& level);
};

#endif
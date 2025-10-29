/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:58:37 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/02 14:10:55 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_HPP
# define HARL_HPP

#include <iostream>
#include <string>

/** @brief Defines the Harl class which simulates different complaint levels.
 *
 * The Harl class provides four private methods corresponding to complaint levels:
 * DEBUG, INFO, WARNING, and ERROR. The public method `complain` selects and executes
 * the appropriate function based on the provided string. The implementation uses
 * pointers to member functions instead of multiple if/else statements.
 */
class Harl{
    private:
        void debug(void);
        void info(void);
        void warning(void);
        void error(void);
    public:
    Harl();
    ~Harl();
    void complain(const std::string& level);

};

#endif
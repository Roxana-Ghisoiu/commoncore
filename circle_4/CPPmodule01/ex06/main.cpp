/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 14:42:13 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/09/02 14:50:17 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

/**
 * @file main.cpp
 * @brief Runs Harl filter: prints messages from the given level and above.
 *
 * Usage:
 *   ./harlFilter "WARNING"
 *   ./harlFilter "INFO"
 *   ./harlFilter "DEBUG"
 *   ./harlFilter "ERROR"
 *   ./harlFilter "something else"
 */
int main(int argc, char** argv) {
    if (argc != 2)
        return 1;

    Harl harl;
    harl.filter(argv[1]);
    return 0;
}
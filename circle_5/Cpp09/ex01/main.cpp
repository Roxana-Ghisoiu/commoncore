/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:32:10 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/13 15:32:13 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

/**
 * @brief Entry point of the RPN program that evaluates a Reverse Polish
 * Notation expression passed as a single argument.
 */

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	try
	{
		RPN		rpn;
		int		result = rpn.evaluate(av[1]);

		std::cout << result << std::endl;
	}
	catch (const std::exception &)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	return (0);
}
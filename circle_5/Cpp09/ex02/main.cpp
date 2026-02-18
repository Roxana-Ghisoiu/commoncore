/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:20:30 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/13 16:21:44 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/**
 * @brief Entry point of the PmergeMe program that parses a sequence
 *        of positive integers from the command line and sorts it using
 *        merge-insert sort with std::vector and std::list, displaying
 *        timing information for both containers.
 */

int	main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	try
	{
		std::vector<int>	baseSequence;

		parseArguments(ac, av, baseSequence);
		if (baseSequence.empty())
		{
			std::cerr << "Error" << std::endl;
			return (1);
		}

		std::cout << "Before: ";
		printContainer(baseSequence);

		clock_t			startVec = clock();
		std::vector<int>	vec = baseSequence;
		sortVector(vec);
		clock_t			endVec = clock();

		clock_t			startList = clock();
		std::list<int>	lst(baseSequence.begin(), baseSequence.end());
		sortList(lst);
		clock_t			endList = clock();

		std::cout << "After:" << std::endl;
		printContainer(vec);

		double	timeVec = static_cast<double>(endVec - startVec) * 1000000.0
			/ CLOCKS_PER_SEC;
		double	timeList = static_cast<double>(endList - startList) * 1000000.0
			/ CLOCKS_PER_SEC;

		std::cout << "Time to process a range of " << baseSequence.size()
			<< " elements with std::vector : "
			<< std::fixed << std::setprecision(5) << timeVec << " us" << std::endl;
		std::cout << "Time to process a range of " << baseSequence.size()
			<< " elements with std::list   : "
			<< std::fixed << std::setprecision(5) << timeList << " us" << std::endl;
	}
	catch (const std::exception &)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	return (0);
}
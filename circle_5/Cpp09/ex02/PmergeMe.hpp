/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:18:46 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/13 16:21:33 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <climits>
#include <algorithm>
#include <ctime>
#include <iomanip>

/**
 * @brief Declaration of helper functions used to parse arguments and
 *        sort a sequence of positive integers using merge-insert sort
 *        with std::vector and std::list containers.
 */

template <typename T>
void	printContainer(const T &container)
{
	typename T::const_iterator it = container.begin();
	typename T::const_iterator end = container.end();
	while (it != end)
	{
		std::cout << *it;
		++it;
		if (it != end)
			std::cout << " ";
	}
	std::cout << std::endl;
}

void	parseArguments(int ac, char **av, std::vector<int> &sequence);
void	sortVector(std::vector<int> &vec);
void	sortList(std::list<int> &lst);

#endif
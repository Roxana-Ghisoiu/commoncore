/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:19:40 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/13 16:21:11 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/**
 * @brief Implementation of argument parsing and merge-insert sort
 *        for std::vector and std::list containers.
 */

void	parseArguments(int ac, char **av, std::vector<int> &sequence)
{
	for (int i = 1; i < ac; ++i)
	{
		std::string	arg(av[i]);
		if (arg.empty())
			throw std::runtime_error("Error");
		for (std::string::size_type j = 0; j < arg.size(); ++j)
		{
			if (!std::isdigit(static_cast<unsigned char>(arg[j])))
				throw std::runtime_error("Error");
		}
		std::istringstream	ss(arg);
		long long			value;
		ss >> value;
		if (ss.fail() || !ss.eof())
			throw std::runtime_error("Error");
		if (value <= 0 || value > INT_MAX)
			throw std::runtime_error("Error");
		sequence.push_back(static_cast<int>(value));
	}
}

void	sortVector(std::vector<int> &vec)
{
	if (vec.size() < 2)
		return;

	std::vector<int>	bigger;
	std::vector<int>	lower;

	for (std::vector<int>::size_type i = 0; i < vec.size(); i += 2)
	{
		if (i + 1 < vec.size())
		{
			int	a = vec[i];
			int	b = vec[i + 1];
			if (a < b)
			{
				bigger.push_back(b);
				lower.push_back(a);
			}
			else
			{
				bigger.push_back(a);
				lower.push_back(b);
			}
		}
		else
			lower.push_back(vec[i]);
	}
	sortVector(bigger);
	for (std::vector<int>::iterator it = lower.begin(); it != lower.end(); ++it)
	{
		int								n = *it;
		std::vector<int>::iterator		pos;

		pos = std::lower_bound(bigger.begin(), bigger.end(), n);
		bigger.insert(pos, n);
	}
	vec = bigger;
}

void	sortList(std::list<int> &lst)
{
	if (lst.size() < 2)
		return;

	std::list<int>	bigger;
	std::list<int>	lower;

	std::list<int>::iterator it = lst.begin();
	while (it != lst.end())
	{
		int	a = *it;
		++it;
		if (it != lst.end())
		{
			int	b = *it;
			if (a < b)
			{
				bigger.push_back(b);
				lower.push_back(a);
			}
			else
			{
				bigger.push_back(a);
				lower.push_back(b);
			}
			++it;
		}
		else
			lower.push_back(a);
	}
	sortList(bigger);
	for (std::list<int>::iterator lit = lower.begin(); lit != lower.end(); ++lit)
	{
		int						n = *lit;
		std::list<int>::iterator	pos;

		pos = std::lower_bound(bigger.begin(), bigger.end(), n);
		bigger.insert(pos, n);
	}
	lst = bigger;
}
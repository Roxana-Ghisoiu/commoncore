/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:00:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/13 15:31:25 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <stdexcept>
#include <cctype>

/**
 * @brief Declaration of the RPN class used to evaluate a Reverse Polish
 * Notation expression using a stack container.
 */

class RPN
{
private:
	std::stack<int>	_stack;

public:
	RPN();
	RPN(const RPN &other);
	RPN &operator=(const RPN &other);
	~RPN();

	int	evaluate(const std::string &expression);
};

#endif
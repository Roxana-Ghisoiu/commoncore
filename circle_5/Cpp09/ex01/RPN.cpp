/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:31:11 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/11/13 15:31:47 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

/**
 * @brief Implementation of the RPN class that evaluates an expression
 * written in Reverse Polish Notation using a stack of integers.
 */

RPN::RPN()
{
}

RPN::RPN(const RPN &other)
{
	*this = other;
}

RPN	&RPN::operator=(const RPN &other)
{
	if (this != &other)
		_stack = other._stack;
	return (*this);
}

RPN::~RPN()
{
}

int	RPN::evaluate(const std::string &expression)
{
	std::istringstream	iss(expression);
	std::string			token;

	while (iss >> token)
	{
		if (token.size() == 1
			&& std::isdigit(static_cast<unsigned char>(token[0])))
		{
			int	value = token[0] - '0';
			_stack.push(value);
		}
		else if (token.size() == 1
			&& (token[0] == '+' || token[0] == '-'
				|| token[0] == '*' || token[0] == '/'))
		{
			if (_stack.size() < 2)
				throw std::runtime_error("Error");
			int	b = _stack.top();
			_stack.pop();
			int	a = _stack.top();
			_stack.pop();
			int	result = 0;
			if (token[0] == '+')
				result = a + b;
			else if (token[0] == '-')
				result = a - b;
			else if (token[0] == '*')
				result = a * b;
			else
			{
				if (b == 0)
					throw std::runtime_error("Error");
				result = a / b;
			}
			_stack.push(result);
		}
		else
			throw std::runtime_error("Error");
	}
	if (_stack.size() != 1)
		throw std::runtime_error("Error");
	return (_stack.top());
}
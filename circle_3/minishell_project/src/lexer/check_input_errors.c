/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_errors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:11:52 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/23 19:17:21 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks for unclosed double quotes in the input string.
 * 
 * @param input The input line.
 * @return true if unclosed double quotes are found, false otherwise.
 */
bool	has_unclosed_double_quotes(const char *input)
{
	bool	in_quote;
	int		i;

	in_quote = false;
	i = 0;
	while (input[i])
	{
		if (input[i] == '"')
			in_quote = !in_quote;
		i++;
	}
	return (in_quote);
}

/**
 * @brief Checks for forbidden characters like `;` or `\` in the input.
 * 
 * @param input The input line.
 * @return true if forbidden characters are present, false otherwise.
 */

/**
 * @brief Checks for forbidden characters like `;` or `\` in the input,
 *        unless they are inside single or double quotes.
 * 
 * @param input The input line.
 * @return true if forbidden characters are
 * found outside quotes, false otherwise.
 */
bool	has_forbidden_chars(const char *input)
{
	int		i;
	bool	in_single;
	bool	in_double;

	i = 0;
	in_single = false;
	in_double = false;
	while (input[i])
	{
		if (input[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (input[i] == '"' && !in_single)
			in_double = !in_double;
		else if ((input[i] == '\\' || input[i] == ';')
			&& !in_single && !in_double)
			return (true);
		i++;
	}
	return (false);
}

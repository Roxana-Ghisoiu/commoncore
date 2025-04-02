/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_errors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:11:52 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/02 14:13:17 by rghisoiu         ###   ########.fr       */
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
bool	has_forbidden_chars(const char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == ';' || input[i] == '\\')
			return (true);
		i++;
	}
	return (false);
}


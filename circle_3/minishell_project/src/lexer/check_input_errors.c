/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_errors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:11:52 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/28 14:18:18 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if the input line contains unclosed single or double quotes.
 * 
 * @param line The input line to check.
 * @return true if quotes are unclosed, false otherwise.
 */
bool	has_unclosed_quotes(char *line)
{
	bool	in_single;
	bool	in_double;
	int		i;

	in_single = false;
	in_double = false;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (line[i] == '"' && !in_single)
			in_double = !in_double;
		i++;
	}
	return (in_single || in_double);
}

/**
 * @brief Check if a line contains forbidden characters.
 * @param line The input line to check.
 * @return 1 if forbidden characters are found, 0 otherwise.
 */
int	has_forbidden_chars(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\\' || line[i] == ';')
			return (1);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_protect_single_quotes.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:53:02 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/11 18:53:06 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Helper function that walks through input and replaces $ with \x01
 * only if currently inside single quotes.
 * 
 * @param input The input string.
 * @param result The result buffer to write into.
 */
static void	replace_dollar_if_in_single_quotes(const char *input, char *result)
{
	int		i;
	int		j;
	bool	in_single;

	i = 0;
	j = 0;
	in_single = false;
	while (input[i])
	{
		if (input[i] == '\'')
			in_single = !in_single;
		if (input[i] == '$' && in_single)
			result[j] = '\x01';
		else
			result[j] = input[i];
		i++;
		j++;
	}
	result[j] = '\0';
}

/**
 * @brief Replace all $ symbols inside single quotes with a special marker
 * to prevent variable expansion during parsing.
 * 
 * @param input Input line.
 * @return A newly allocated string with protected content.
 */
char	*protect_dollar_in_single_quotes(const char *input)
{
	char	*result;

	if (!input)
		return (NULL);
	result = malloc(ft_strlen(input) + 1);
	if (!result)
		return (NULL);
	replace_dollar_if_in_single_quotes(input, result);
	return (result);
}

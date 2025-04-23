/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_protect_single_quotes.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:53:02 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/23 12:50:07 by rghisoiu         ###   ########.fr       */
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

/**
 * @brief Handles a protected dollar character (\x01),
 * which was originally a $ inside single quotes.
 *
 * @param i Pointer to index in input string.
 * @return Allocated string containing literal '$'.
 */
char	*handle_protected_dollar(int *i)
{
	char	*chunk;

	chunk = ft_calloc(2, 1);
	if (!chunk)
		return (NULL);
	chunk[0] = '$';
	(*i)++;
	return (chunk);
}

/**
 * @brief Selects and returns the appropriate chunk based on input at index i.
 */
char	*select_expansion_chunk(t_shell *sh, const char *input, int *i)
{
	if (input[*i] == '$' && input[*i + 1] == '?')
		return (handle_exit_code(sh, i));
	else if (input[*i] == '$' && input[*i + 1]
		&& (ft_isalnum(input[*i + 1]) || input[*i + 1] == '_'))
		return (handle_variable(sh, input, i));
	else if (input[*i] == '\x01')
		return (handle_protected_dollar(i));
	else
		return (handle_char(input, i));
}

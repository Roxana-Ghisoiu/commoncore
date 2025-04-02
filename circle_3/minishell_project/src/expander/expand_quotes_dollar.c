/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes_dollar.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:04:12 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/01 11:07:49 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Removes double quotes from input but preserves the content,
 *        including $ for later variable expansion.
 * 
 * @param input The input string (possibly containing double quotes)
 * @return A newly allocated string without double quotes. NULL on malloc fail.
 */
char	*remove_double_quotes_preserve_dollar(const char *input)
{
	char	*result;
	int		i;
	int		j;
	int		in_double_quotes;
	int		len;

	if (!input)
		return (NULL);
	len = ft_strlen(input);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	in_double_quotes = 0;
	while (input[i])
	{
		if (input[i] == '"')
			in_double_quotes = !in_double_quotes;
		else
			result[j++] = input[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:25:40 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/11 18:16:53 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_single_quotes(const char *input)
{
	char	*result;
	int		i;
	int		j;
	bool	in_quote;

	result = malloc(ft_strlen(input) + 1);
	if (!result)
		return (NULL);
	i = -1;
	j = 0;
	in_quote = false;
	while (input[++i])
	{
		if (input[i] == '\'')
			in_quote = !in_quote;
		else
			result[j++] = input[i];
	}
	result[j] = '\0';
	return (result);
}

bool	has_unclosed_single_quotes(const char *input)
{
	bool	in_quote;
	int		i;

	in_quote = false;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			in_quote = !in_quote;
		i++;
	}
	return (in_quote);
}

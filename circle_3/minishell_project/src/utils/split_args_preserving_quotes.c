/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_preserving_quotes.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:20:23 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/28 16:29:17 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

static void	skip_quoted_section(const char *str, int *i)
{
	char	quote;

	quote = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (str[*i])
		(*i)++;
}

static char	*extract_arg(const char *str, int *i)
{
	int		start;

	while (str[*i] && str[*i] == ' ')
		(*i)++;
	start = *i;
	while (str[*i])
	{
		if (is_quote(str[*i]))
			skip_quoted_section(str, i);
		else if (str[*i] == ' ')
			break ;
		else
			(*i)++;
	}
	return (ft_substr(str, start, *i - start));
}

static void	fill_args(const char *input, char **args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		args[count++] = extract_arg(input, &i);
		while (input[i] && input[i] == ' ')
			i++;
	}
	args[count] = NULL;
}

char	**split_args_preserving_quotes(const char *input)
{
	char	**args;

	args = ft_calloc(1024, sizeof(char *));
	if (!args)
		return (NULL);
	fill_args(input, args);
	return (args);
}

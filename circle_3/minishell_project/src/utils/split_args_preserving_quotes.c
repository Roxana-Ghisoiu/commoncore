/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_preserving_quotes.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:03:54 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/09 10:43:16 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_preserving_quotes.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:03:54 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/08 10:28:00 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if the character is a quote.
 *
 * @param c The character to check.
 * @return 1 if character is a quote, 0 otherwise.
 */
static int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

/**
 * @brief Extracts the next argument, preserving quotes.
 *
 * @param str Input string.
 * @param i Index pointer.
 * @return Newly allocated string.
 */
static char	*extract_arg(const char *str, int *i)
{
	int		start;
	char	quote;

	while (str[*i] && str[*i] == ' ')
		(*i)++;
	start = *i;
	if (is_quote(str[*i]))
	{
		quote = str[(*i)++];
		while (str[*i] && str[*i] != quote)
			(*i)++;
		if (str[*i])
			(*i)++;
	}
	else
	{
		while (str[*i] && str[*i] != ' ')
			(*i)++;
	}
	return (ft_substr(str, start, *i - start));
}

/**
 * @brief Splits the input string into arguments, preserving quotes.
 *
 * @param input Raw input line.
 * @return NULL-terminated array of arguments.
 */
char	**split_args_preserving_quotes(const char *input)
{
	char	**args;
	int		i;
	int		count;

	args = ft_calloc(1024, sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	count = 0;
	while (input[i])
	{
		args[count++] = extract_arg(input, &i);
		while (input[i] && input[i] == ' ')
			i++;
	}
	args[count] = NULL;
	return (args);
}

bool	is_quoted(const char *str)
{
	size_t	len;

	if (!str)
		return (false);
	len = ft_strlen(str);
	if (len < 2)
		return (false);
	return ((str[0] == '\'' && str[len - 1] == '\'')
		|| (str[0] == '\"' && str[len - 1] == '\"'));
}

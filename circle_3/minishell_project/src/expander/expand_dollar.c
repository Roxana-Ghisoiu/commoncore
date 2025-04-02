/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:12:26 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/01 16:59:02 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handles full expansion: removes double quotes,
 * expands vars, handles '*'.
 * 
 * @param sh The shell struct containing env list.
 * @param input The raw input line from the user.
 * @return A newly allocated string with quotes removed, vars and '*' expanded.
 */
char	*expand_line(t_shell *sh, const char *input)
{
	char	*without_quotes;
	char	*expanded_vars;
	char	*final_line;

	if (!input)
		return (NULL);
	without_quotes = remove_double_quotes_preserve_dollar(input);
	if (!without_quotes)
		return (NULL);
	expanded_vars = expand_env_variables(sh, without_quotes);
	free(without_quotes);
	if (!expanded_vars)
		return (NULL);
	if (has_unquoted_asterisk(expanded_vars))
	{
		final_line = replace_asterisk_with_files(expanded_vars);
		free(expanded_vars);
		return (final_line);
	}
	return (expanded_vars);
}

static char	*handle_variable(t_shell *sh, const char *input, int *i)
{
	char	*var_name;
	char	*var_value;
	char	*joined;

	var_name = extract_var_name(&input[*i + 1]);
	var_value = get_env_value(sh->env_list, var_name);
	if (var_value)
		joined = ft_strdup(var_value);
	else
		joined = ft_strdup("");
	*i += ft_strlen(var_name) + 1;
	free(var_name);
	return (joined);
}

/**
 * @brief Returns the next character as a string when not a variable.
 */
static char	*handle_char(const char *input, int *i)
{
	char	*chunk;

	chunk = ft_calloc(2, 1);
	if (chunk)
		chunk[0] = input[*i];
	(*i)++;
	return (chunk);
}

/**
 * @brief Expands environment variables ($VAR) in the input string.
 */
char	*expand_env_variables(t_shell *sh, const char *input)
{
	char	*result;
	char	*temp;
	char	*chunk;
	int		i;

	result = ft_calloc(1, 1);
	if (!result)
		return (NULL);
	i = 0;
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1]
			&& (ft_isalnum(input[i + 1]) || input[i + 1] == '_'))
			chunk = handle_variable(sh, input, &i);
		else
			chunk = handle_char(input, &i);
		temp = ft_strjoin(result, chunk);
		free(result);
		free(chunk);
		result = temp;
	}
	return (result);
}

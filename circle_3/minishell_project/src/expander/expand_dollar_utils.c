/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:01:20 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/23 13:07:43 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Extracts and returns the value of an environment variable.
 */

char	*handle_variable(t_shell *sh, const char *input, int *i)
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
 * @brief Expands $? to the last exit code.
 */

char	*handle_exit_code(t_shell *sh, int *i)
{
	char	*chunk;

	chunk = ft_itoa(sh->exit_code);
	*i += 2;
	return (chunk);
}

/**
 * @brief Returns a string with a single character from input[i].
 */

char	*handle_char(const char *input, int *i)
{
	char	*chunk;

	chunk = ft_calloc(2, 1);
	if (chunk)
		chunk[0] = input[*i];
	(*i)++;
	return (chunk);
}

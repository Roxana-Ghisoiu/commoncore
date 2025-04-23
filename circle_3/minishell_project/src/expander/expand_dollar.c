/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:12:26 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/23 13:10:05 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handles full expansion: quotes, variables, and globbing (*).
 * 
 * @param sh The shell context.
 * @param input Raw input line.
 * @return Final expanded line.
 */

char	*expand_line(t_shell *sh, const char *input)
{
	char	*protected;
	char	*expanded;

	if (!input)
		return (NULL);
	protected = protect_dollar_in_single_quotes(input);
	if (!protected)
		return (NULL);
	expanded = expand_env_variables(sh, protected);
	free(protected);
	return (expanded);
}

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
		chunk = select_expansion_chunk(sh, input, &i);
		temp = ft_strjoin(result, chunk);
		free(result);
		free(chunk);
		result = temp;
	}
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_globbing_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:47:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/08 12:00:00 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if input string contains unquoted asterisk.
 * 
 * @param str The string to check.
 * @return true if unquoted asterisk is found.
 */
bool	has_unquoted_asterisk(const char *str)
{
	bool	in_double;
	bool	in_single;
	int		i;

	in_double = false;
	in_single = false;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '"' && !in_single)
			in_double = !in_double;
		else if (str[i] == '*' && !in_single && !in_double)
			return (true);
		i++;
	}
	return (false);
}

/**
 * @brief Replace '*' with matching files from current directory.
 * 
 * @param input Input string possibly containing '*'.
 * @return Expanded string with files instead of '*'.
 */
char	*replace_asterisk_with_files(const char *input)
{
	char	**files;
	char	*result;
	int		i;

	files = expand_asterisk();
	if (!files)
		return (ft_strdup(input));
	result = ft_calloc(1, 1);
	if (!result)
		return (NULL);
	i = 0;
	while (files[i])
	{
		result = ft_strjoin_free(result, files[i]);
		result = ft_strjoin_free(result, " ");
		i++;
	}
	ft_free_split(files);
	return (result);
}

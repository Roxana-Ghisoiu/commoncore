/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_globbing_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:48:09 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/01 15:34:57 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_globbing_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:30:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/01 13:30:00 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_globbing_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:47:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/01 12:47:00 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if input contains unquoted * (outside of ' ' or " ").
 * 
 * @param str The input string to scan.
 * @return true if unquoted * is found, false otherwise.
 */
bool	has_unquoted_asterisk(const char *str)
{
	bool	in_single;
	bool	in_double;
	int		i;

	in_single = false;
	in_double = false;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '\"' && !in_single)
			in_double = !in_double;
		else if (str[i] == '*' && !in_single && !in_double)
			return (true);
		i++;
	}
	return (false);
}

/**
 * @brief Replaces * in input with all matching files (non-hidden).
 * 
 * @param input The original input string.
 * @return A newly allocated string with * replaced by file list.
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_is_quoted.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:25:27 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/28 16:27:05 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if a string is enclosed entirely in quotes.
 * 
 * @param str The string to check.
 * @return true if quoted, false otherwise.
 */
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

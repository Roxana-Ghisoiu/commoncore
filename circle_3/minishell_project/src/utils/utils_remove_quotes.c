/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_remove_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:37:18 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/28 16:37:25 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Removes surrounding quotes from a string if they exist.
 * 
 * @param str The input string.
 * @return Newly allocated string without surrounding quotes.
 */
char	*remove_surrounding_quotes(const char *str)
{
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len >= 2 && ((str[0] == '"' && str[len - 1] == '"')
			|| (str[0] == '\'' && str[len - 1] == '\'')))
		return (ft_substr(str, 1, len - 2));
	return (ft_strdup(str));
}

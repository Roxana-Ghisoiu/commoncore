/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_is_valid_varname.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:40:28 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/28 16:26:40 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if a variable name is valid.
 * 
 * @param var The variable name to check.
 * @return int 1 if valid, 0 if invalid.
 */
int	is_valid_varname(const char *var)
{
	int	i;

	if (!var || !*var)
		return (0);
	if (!isalpha(var[0]) && var[0] != '_')
		return (0);
	i = 1;
	while (var[i] && var[i] != '=')
	{
		if (!isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

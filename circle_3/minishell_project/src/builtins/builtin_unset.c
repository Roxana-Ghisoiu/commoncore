/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:43:56 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/24 12:44:23 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Removes variables from the environment list.
 * 
 * @param sh The shell structure.
 * @param args List of variable names to unset.
 * @return int Always returns 0.
 */
int	builtin_unset(t_shell *sh, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		remove_env_var(&sh->env_list, args[i]);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:45:14 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/24 12:48:15 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Adds or updates environment variables.
 * 
 * @param sh The shell structure.
 * @param args The arguments (KEY=VALUE format).
 * @param fd_out The output file descriptor.
 * @return int Always returns 0.
 */
int	builtin_export(t_shell *sh, char **args, int fd_out)
{
	int		i;
	char	*equal;

	if (!args[1])
		return (builtin_env(sh, fd_out));
	i = 1;
	while (args[i])
	{
		equal = ft_strchr(args[i], '=');
		if (equal)
		{
			*equal = '\0';
			update_env_var(&sh->env_list, args[i], equal + 1);
			*equal = '=';
		}
		i++;
	}
	return (0);
}

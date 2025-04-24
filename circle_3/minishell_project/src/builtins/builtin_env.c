/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:40:25 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/24 13:08:05 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints all environment variables (key=value).
 * 
 * @param sh The shell structure.
 * @param fd_out The output file descriptor.
 * @return int 0.
 */
int	builtin_env(t_shell *sh, int fd_out)
{
	t_env	*env;

	env = sh->env_list;
	while (env)
	{
		if (env->value)
		{
			ft_putstr_fd(env->key, fd_out);
			ft_putchar_fd('=', fd_out);
			ft_putendl_fd(env->value, fd_out);
		}
		env = env->next;
	}
	return (0);
}

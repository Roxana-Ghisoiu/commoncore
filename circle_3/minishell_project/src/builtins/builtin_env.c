/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:40:25 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/29 11:16:25 by rghisoiu         ###   ########.fr       */
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
#include "minishell.h"

/**
 * @brief Prints all environment variables (key=value).
 * 
 * @param sh The shell structure.
 * @param args The arguments given to env command.
 * @param fd_out The output file descriptor.
 * @return int 0 on success, 1 if error.
 */
int	builtin_env(t_shell *sh, char **args, int fd_out)
{
	t_env	*env;

	if (args && args[1])
	{
		ft_putendl_fd("env: too many arguments", STDERR_FILENO);
		return (1);
	}
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

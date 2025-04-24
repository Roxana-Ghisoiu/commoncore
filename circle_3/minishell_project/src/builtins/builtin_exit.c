/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:46:55 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/24 15:12:35 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if a string is numeric (allows + / -).
 *
 * @param str The string to check.
 * @return 1 if valid numeric string, 0 otherwise.
 */
static int	has_only_digits(const char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Builtin exit command: exits the shell with optional status.
 *
 * Handles:
 * - `exit` → uses last status
 * - `exit 42` → exits with status 42
 * - `exit abc` → numeric error, exits with 255
 * - `exit 1 2` → too many arguments, does not exit
 *
 * @param sh The shell structure.
 * @param args The command arguments.
 * @return int 1 if too many args, otherwise never returns.
 */
int	builtin_exit(t_shell *sh, char **args)
{
	printf("exit\n");
	if (args[1])
	{
		if (!has_only_digits(args[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			free_shell(sh);
			cleanup_readline();
			exit(255);
		}
		if (args[2])
		{
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			sh->exit_code = 1;
			return (1);
		}
		sh->exit_code = ft_atoi(args[1]) % 256;
	}
	free_shell(sh);
	cleanup_readline();
	exit(sh->exit_code);
}

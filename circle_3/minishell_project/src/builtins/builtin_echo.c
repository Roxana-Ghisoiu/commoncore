/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:07:42 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/24 21:36:17 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if the given string is a valid -n option (e.g., -n, -nnn).
 * 
 * @param arg The argument to check.
 * @return 1 if it's a valid -n option, 0 otherwise.
 */
static int	is_n_flag(const char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (i > 1);
}

/**
 * @brief Implementation of the echo builtin with support for -n option.
 * 
 * Prints arguments to the specified output file descriptor.
 * Suppresses the newline at the end if -n is provided.
 * 
 * @param args The command arguments.
 * @param fd_out The output file descriptor.
 * @return Always returns 0.
 */
int	builtin_echo(char **args, int fd_out)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (args[i] && is_n_flag(args[i]))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], fd_out);
		if (args[i + 1])
			ft_putchar_fd(' ', fd_out);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', fd_out);
	return (0);
}

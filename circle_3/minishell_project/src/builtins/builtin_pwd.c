/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:38:47 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/24 15:13:13 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints the current working directory.
 * 
 * @param args The command arguments (args[0] = "pwd").
 * @param fd_out The output file descriptor.
 * @return int 0 on success, 1 on error.
 */
int	builtin_pwd(char **args, int fd_out)
{
	char	*cwd;

	if (args[1])
	{
		ft_putendl_fd("minishell: pwd: too many arguments", 2);
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("minishell: pwd");
		return (1);
	}
	ft_putendl_fd(cwd, fd_out);
	free(cwd);
	return (0);
}

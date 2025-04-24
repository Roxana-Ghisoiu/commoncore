/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:37:06 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/24 15:13:37 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if the command is a built-in command.
 *
 * @param cmd The command to check.
 * @return 1 if it is a built-in command, 0 otherwise.
 */

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (ft_strncmp(cmd, "echo", 5) == 0
		|| ft_strncmp(cmd, "cd", 3) == 0
		|| ft_strncmp(cmd, "pwd", 4) == 0
		|| ft_strncmp(cmd, "export", 7) == 0
		|| ft_strncmp(cmd, "unset", 6) == 0
		|| ft_strncmp(cmd, "env", 4) == 0
		|| ft_strncmp(cmd, "exit", 5) == 0);
}

/**
  * @brief Execute a built-in command.
  *
  * @param sh The shell data.
  * @param node The node containing command and arguments.
  * @param fd_out The file descriptor for output redirection.
  * @return Exit status of the executed command.
  */

int	execute_builtin(t_shell *sh, t_node *node, int fd_out)
{
	if (ft_strncmp(node->args[0], "echo", 5) == 0)
		return (builtin_echo(node->args, fd_out));
	if (ft_strncmp(node->args[0], "cd", 3) == 0)
		return (builtin_cd(sh, node->args));
	if (ft_strncmp(node->args[0], "pwd", 4) == 0)
		return (builtin_pwd(node->args, fd_out));
	if (ft_strncmp(node->args[0], "export", 7) == 0)
		return (builtin_export(sh, node->args, fd_out));
	if (ft_strncmp(node->args[0], "unset", 6) == 0)
		return (builtin_unset(sh, node->args));
	if (ft_strncmp(node->args[0], "env", 4) == 0)
		return (builtin_env(sh, fd_out));
	if (ft_strncmp(node->args[0], "exit", 5) == 0)
		return (builtin_exit(sh, node->args));
	return (1);
}

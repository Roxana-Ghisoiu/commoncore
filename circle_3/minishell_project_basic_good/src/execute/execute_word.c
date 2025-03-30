/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:51:57 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/03/27 14:52:07 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Execute a command node (non-builtin).
 *
 * @param sh The shell data.
 * @param node The node containing command and arguments.
 * @return Exit status of the executed command.
 */
int	execute_word(t_shell *sh, t_node *node)
{
	char	*path;
	int		status;

	if (!node || !node->args || !node->args[0])
		return (1);
	path = find_command_path(sh, node->args[0]);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(node->args[0], 2);
		return (127);
	}
	status = fork_and_execute(sh, path, node->args);
	free(path);
	return (status);
}

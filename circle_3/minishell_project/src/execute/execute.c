/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:06:01 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/28 13:41:40 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Executes a command node or pipe with possible redirections.
 * 
 * Handles command execution, including redirections and pipes.
 * Delegates pipe logic to execute_pipe_node if node is of type TOK_PIPE.
 * 
 * @param sh Pointer to the shell context.
 * @param node The root node of the command or pipe to execute.
 * @return int Exit status.
 */
int	execute_command(t_shell *sh, t_node *node)
{
	char	*path;
	int		status;

	if (!node || !node->args || !node->args[0])
		return (0);
	if (handle_builtin_if_needed(sh, node))
		return (sh->exit_code);
	path = find_command_path(sh, node->args[0]);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(node->args[0], 2);
		return (127);
	}
	status = execute_with_redir(sh, path, node->args, node);
	free(path);
	return (status);
}

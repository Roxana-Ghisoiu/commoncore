/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:06:01 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/16 18:59:53 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Executes a command node with possible redirections.
 * 
 * Handles input/output/heredoc redirections using the prepared
 * functions and then executes the command with execute_with_redir.
 * 
 * @param sh Pointer to the shell context.
 * @param node The root node of the command to execute.
 * @return int Exit status.
 */
int	execute_command(t_shell *sh, t_node *node)
{
	char	*path;

	if (!node || !node->args || !node->args[0])
		return (0);
	path = find_command_path(sh, node->args[0]);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(node->args[0], 2);
		return (127);
	}
	return (execute_with_redir(sh, path, node->args, node));
}

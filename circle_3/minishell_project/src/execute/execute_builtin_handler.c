/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_handler.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:20:41 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/28 15:50:58 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handles builtin execution if the command is a builtin,
 * including applying redirections if needed.
 * 
 * @param sh The shell structure.
 * @param node The command node.
 * @return 1 if builtin executed, 0 if not a builtin.
 */
int	handle_builtin_if_needed(t_shell *sh, t_node *node)
{
	int	status;
	int	saved_stdout;
	int	fd_out;

	if (!node || !node->args || !node->args[0])
		return (0);
	if (!is_builtin(node->args[0]))
		return (0);
	saved_stdout = dup(STDOUT_FILENO);
	if (prepare_redirections(node) != 0)
	{
		close(saved_stdout);
		return (1);
	}
	fd_out = STDOUT_FILENO;
	if (node->type == TOK_REDIR_OUT || node->type == TOK_APPEND)
		fd_out = execute_open_output_file(node);
	status = execute_builtin(sh, node, fd_out);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	sh->exit_code = status;
	return (1);
}

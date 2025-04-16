/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:51:52 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/15 17:11:48 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_input(t_node *node)
{
	int	fd;

	fd = execute_open_input_file(node);
	if (fd == -1)
		return (1);
	if (fd != STDIN_FILENO)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			return (1);
		close(fd);
	}
	return (0);
}

static int	redirect_output(t_node *node)
{
	int	fd;

	fd = execute_open_output_file(node);
	if (fd == -1)
		return (1);
	if (fd != STDOUT_FILENO)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (1);
		close(fd);
	}
	return (0);
}

/**
 * @brief Prepares redirections before executing the command.
 * 
 * This includes heredoc, input and output redirections.
 * 
 * @param node The command node.
 * @return int 0 on success, 1 on error.
 */
int	prepare_redirections(t_node *node)
{
	if (!node)
		return (1);
	if (node->heredoc_fd != -1)
	{
		if (dup2(node->heredoc_fd, STDIN_FILENO) == -1)
			return (1);
		close(node->heredoc_fd);
	}
	if (redirect_input(node))
		return (1);
	if (redirect_output(node))
		return (1);
	return (0);
}

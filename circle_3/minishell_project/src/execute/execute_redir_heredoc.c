/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir_heredoc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:20:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/16 19:02:34 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Reads lines from the user until the limiter is matched.
 * 
 * Stores each line entered by the user (via readline) in a temporary
 * pipe which will act as the stdin during command execution.
 * 
 * @param limiter The string that ends heredoc input.
 * @return int The file descriptor to be used as STDIN, or -1 on error.
 */

int	execute_handle_heredoc(const char *limiter)
{
	char	*line;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), -1);
	while (1)
	{
		line = readline("> ");
		if (!line || (ft_strlen(line) == ft_strlen(limiter)
				&& ft_strncmp(line, limiter, ft_strlen(limiter)) == 0))
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

/**
 * @brief Recursively processes heredoc nodes and stores file descriptor.
 * 
 * Traverses the execution tree and, for each node of type TOK_HEREDOC,
 * it generates a heredoc pipe and stores the file descriptor in the node.
 * 
 * @param node Root of the execution tree.
 * @return int 0 on success, 1 on error.
 */

int	execute_process_heredocs(t_node *node)
{
	if (!node)
		return (0);
	if (node->type == TOK_HEREDOC && node->value)
	{
		node->heredoc_fd = execute_handle_heredoc(node->value);
		if (node->heredoc_fd == -1)
			return (1);
		if (node->left && node->left->type == TOK_WORD)
			node->left->heredoc_fd = node->heredoc_fd;
		else if (node->right && node->right->type == TOK_WORD)
			node->right->heredoc_fd = node->heredoc_fd;
	}
	if (execute_process_heredocs(node->left))
		return (1);
	if (execute_process_heredocs(node->right))
		return (1);
	return (0);
}

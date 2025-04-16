/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir_output.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:12:16 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/15 15:28:43 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Opens an output file with the correct flags based on redirection type.
 * 
 * @param file Filename to open.
 * @param type TOK_REDIR_OUT or TOK_APPEND.
 * @return File descriptor or -1 on error.
 */
static int	open_output_target_file(char *file, t_token_type type)
{
	int	fd;

	if (type == TOK_REDIR_OUT)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(file);
	}
	return (fd);
}

/**
 * @brief Opens the output file(s) specified by redirection nodes.
 * 
 * Traverses the right subtree of the node and opens any > or >> files.
 * 
 * @param node The command node.
 * @return The last file descriptor opened, or -1 on error.
 */
int	execute_open_output_file(t_node *node)
{
	t_node	*curr;
	int		fd;
	int		last_fd;
	char	*file;

	curr = node->right;
	last_fd = 1;
	while (curr)
	{
		if (curr->type == TOK_REDIR_OUT || curr->type == TOK_APPEND)
		{
			file = curr->value;
			if (last_fd != 1)
				close(last_fd);
			fd = open_output_target_file(file, curr->type);
			if (fd == -1)
				return (-1);
			last_fd = fd;
		}
		curr = curr->right;
	}
	return (last_fd);
}

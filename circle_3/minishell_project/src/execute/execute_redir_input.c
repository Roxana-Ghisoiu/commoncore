/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:05:29 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/15 12:06:25 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Opens the input file(s) specified by redirection nodes.
 * 
 * This function traverses the left subtree of the command node to find
 * any TOK_REDIR_IN nodes (input redirection, `<`). It opens the file(s)
 * for reading and returns the last file descriptor opened. If any file
 * fails to open, the function prints an error and returns -1.
 * 
 * @param node The command node (usually root of a simple command).
 * @return int File descriptor of the input file, or -1 on failure.
 */
int	execute_open_input_file(t_node *node)
{
	t_node	*curr;
	int		fd;
	char	*file;

	curr = node->left;
	fd = 0;
	while (curr)
	{
		if (curr->type == TOK_REDIR_IN)
		{
			file = curr->value;
			if (fd > 0)
				close(fd);
			fd = open(file, O_RDONLY);
			if (fd < 0)
			{
				ft_putstr_fd("minishell: ", 2);
				perror(file);
				return (-1);
			}
		}
		curr = curr->right;
	}
	return (fd);
}

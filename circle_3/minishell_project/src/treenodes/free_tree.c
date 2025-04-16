/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:29:32 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/15 13:29:39 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Frees a command execution tree.
 * 
 * This function frees a node and its left/right children,
 * as well as the value and argument list.
 * 
 * @param node The root of the execution tree.
 */
void	free_tree(t_node *node)
{
	int	i;

	if (!node)
		return ;
	free_tree(node->left);
	free_tree(node->right);
	if (node->value)
		free(node->value);
	if (node->args)
	{
		i = 0;
		while (node->args[i])
		{
			free(node->args[i]);
			i++;
		}
		free(node->args);
	}
	if (node->heredoc_fd != -1)
		close(node->heredoc_fd);
	free(node);
}

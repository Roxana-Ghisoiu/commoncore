/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:29:49 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/16 19:13:53 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief If current node has a HEREDOC in its children, inherit its fd.
 *
 * This ensures that the command node receives the heredoc_fd from
 * its left or right child (where the heredoc redirection was stored).
 *
 * @param node The command node (typically sh->root)
 */
void	inherit_heredoc_fd(t_node *node)
{
	if (!node)
		return ;
	if (node->left && node->left->type == TOK_HEREDOC)
		node->heredoc_fd = node->left->heredoc_fd;
	else if (node->right && node->right->type == TOK_HEREDOC)
		node->heredoc_fd = node->right->heredoc_fd;
}

/**
 * @brief Executes the command tree after parsing and heredoc processing.
 *
 * Applies heredoc fd inheritance, executes the command,
 * and frees the parse tree and tokens after execution.
 *
 * @param sh The shell structure.
 */
void	execute_parsed_tree(t_shell *sh)
{
	if (execute_process_heredocs(sh->root) == 0)
	{
		inherit_heredoc_fd(sh->root);
		execute_command(sh, sh->root);
	}
	free_tree(sh->root);
	sh->root = NULL;
	free_tokens(sh->tokens);
	sh->tokens = NULL;
}

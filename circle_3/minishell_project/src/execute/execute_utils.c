/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:29:49 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/24 14:31:39 by rghisoiu         ###   ########.fr       */
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
	if (node->left)
	{
		if (node->left->heredoc_fd > 0)
			node->heredoc_fd = node->left->heredoc_fd;
		else
			inherit_heredoc_fd(node->left);
	}
	if (node->right)
	{
		if (node->right->heredoc_fd > 0 && node->heredoc_fd == 0)
			node->heredoc_fd = node->right->heredoc_fd;
		else
			inherit_heredoc_fd(node->right);
	}
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
	if (execute_process_heredocs(sh->root) != 0)
	{
		sh->exit_code = 1;
	}
	else
	{
		inherit_heredoc_fd(sh->root);
		if (sh->root && sh->root->type == TOK_WORD
			&& sh->root->args && sh->root->args[0]
			&& is_builtin(sh->root->args[0]))
		{
			sh->exit_code = execute_builtin(sh, sh->root, STDOUT_FILENO);
		}
		else
		{
			sh->exit_code = evaluate_execution(sh, sh->root);
		}
	}
	free_tree(sh->root);
	sh->root = NULL;
	free_tokens(sh->tokens);
	sh->tokens = NULL;
}

/**
 * @brief Decides how to execute a node (pipe or simple command).
 *
 * If the node is a pipe, it will call the pipe executor,
 * otherwise it executes a single command node.
 *
 * @param sh Shell context structure.
 * @param node The node to be executed.
 * @return Exit status of the executed command.
 */
int	evaluate_execution(t_shell *sh, t_node *node)
{
	if (!node)
		return (1);
	if (node->type == TOK_PIPE)
		return (execute_pipe_node(sh, node));
	else
		return (execute_command(sh, node));
}

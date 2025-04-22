/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:33:36 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/22 18:30:32 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Creates a new node representing a pipe.
 *
 * Allocates and initializes a t_node with type TOK_PIPE,
 * and assigns left and right subtrees.
 *
 * @param left Left child node (command before the pipe).
 * @param right Right child node (command after the pipe).
 * @return Pointer to the new pipe node, or NULL on error.
 */
t_node	*create_pipe_node(t_node *left, t_node *right)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = TOK_PIPE;
	node->value = NULL;
	node->args = NULL;
	node->heredoc_fd = -1;
	node->left = left;
	node->right = right;
	return (node);
}

/**
 * @brief Builds the full execution tree from token list.
 *
 * Starts parsing the tokens into a structured tree,
 * supporting commands, redirections, and pipes.
 *
 * @param tokens Pointer to the token list.
 * @return Root of the constructed parse tree.
 */
t_node	*build_parse_tree(t_token **tokens)
{
	t_node	*root;

	if (!tokens || !*tokens)
		return (NULL);
	root = parse_pipeline(tokens);
	return (root);
}

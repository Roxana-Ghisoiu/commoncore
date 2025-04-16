/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:17:26 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/16 18:01:03 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Creates a new t_node with the given type and value.
 * 
 * Allocates a t_node and initializes its fields.
 * 
 * @param type Token type for the node.
 * @param value String value (can be NULL).
 * @return Pointer to the new node, or NULL on failure.
 */
static t_node	*create_node(t_token_type type, char *value)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = type;
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	node->args = NULL;
	node->heredoc_fd = -1;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

/**
 * @brief Fills redirection nodes from the token list.
 * 
 * Sets left and right redirection nodes based on redirection token types.
 * 
 * @param cmd_node The command node to fill.
 * @param tokens The list of tokens.
 */
static void	parse_redirections(t_node *cmd_node, t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	while (curr && curr->type != TOK_PIPE)
	{
		if ((curr->type == TOK_REDIR_IN || curr->type == TOK_HEREDOC)
			&& curr->next)
		{
			cmd_node->left = create_node(curr->type, curr->next->content);
			if (curr->type == TOK_HEREDOC)
				cmd_node->heredoc_fd = cmd_node->left->heredoc_fd;
		}
		else if ((curr->type == TOK_REDIR_OUT || curr->type == TOK_APPEND)
			&& curr->next)
			cmd_node->right = create_node(curr->type, curr->next->content);
		curr = curr->next;
	}
}

/**
 * @brief Parses a simple command from token list and builds an execution node.
 * 
 * Handles command arguments and redirections (<, >, >>, <<).
 * 
 * @param tokens Pointer to token list.
 * @return Pointer to root node of command, or NULL on failure.
 */
t_node	*parse_command(t_token **tokens)
{
	t_node	*cmd_node;

	if (!tokens || !*tokens)
		return (NULL);
	cmd_node = create_node(TOK_WORD, NULL);
	if (!cmd_node)
		return (NULL);
	if (parse_args(cmd_node, *tokens))
		return (NULL);
	parse_redirections(cmd_node, *tokens);
	return (cmd_node);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:05:26 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/23 18:39:54 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Splits token list at the pipe and builds subtrees.
 *
 * Parses left side as a command and right side as another pipeline.
 *
 * @param pipe_token The current token of type TOK_PIPE.
 * @param start The start of the token list.
 * @return Pipe node combining left and right subtrees.
 */
static t_node	*handle_pipe_split(t_token *pipe_token, t_token *start)
{
	t_token		*after_pipe;
	t_node		*left;
	t_node		*right;
	t_node		*pipe_node;

	after_pipe = pipe_token->next;
	pipe_token->next = NULL;
	left = parse_command(&start);
	if (!left)
		return (NULL);
	right = parse_pipeline(&after_pipe);
	if (!right)
		return (NULL);
	pipe_node = create_pipe_node(left, right);
	if (left->heredoc_fd > 0)
		pipe_node->heredoc_fd = left->heredoc_fd;
	return (pipe_node);
}

/**
 * @brief Parses a pipeline from the token list.
 *
 * Recursively builds an execution tree with TOK_PIPE nodes for each pipe found.
 * If no pipe is found, it parses a simple command.
 *
 * @param tokens Pointer to the list of tokens.
 * @return Pointer to the root node of the pipeline.
 */
t_node	*parse_pipeline(t_token **tokens)
{
	t_token	*start;
	t_token	*curr;

	start = *tokens;
	curr = *tokens;
	while (curr)
	{
		if (curr->type == TOK_PIPE)
			return (handle_pipe_split(curr, start));
		curr = curr->next;
	}
	return (parse_command(tokens));
}

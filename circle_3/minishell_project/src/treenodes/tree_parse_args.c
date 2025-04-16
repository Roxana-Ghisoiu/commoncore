/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_parse_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:01:19 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/15 20:26:10 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Fills the command node with its arguments from tokens,
 *        excluding redirection targets.
 * 
 * Counts TOK_WORD tokens that are not part of redirection and
 * duplicates their content into cmd_node->args.
 * 
 * @param cmd_node The command node to fill.
 * @param tokens The list of tokens.
 * @return 0 on success, 1 on allocation error.
 */
static int	is_valid_arg(t_token *curr, t_token *prev)
{
	if (curr->type != TOK_WORD)
		return (0);
	if (!prev)
		return (1);
	if (prev->type == TOK_REDIR_IN || prev->type == TOK_REDIR_OUT
		|| prev->type == TOK_APPEND || prev->type == TOK_HEREDOC)
		return (0);
	return (1);
}

static int	count_args(t_token *tokens)
{
	int			count;
	t_token		*curr;
	t_token		*prev;

	count = 0;
	curr = tokens;
	prev = NULL;
	while (curr && curr->type != TOK_PIPE)
	{
		if (is_valid_arg(curr, prev))
			count++;
		prev = curr;
		curr = curr->next;
	}
	return (count);
}

static void	fill_args(t_node *cmd_node, t_token *tokens)
{
	int			i;
	t_token		*curr;
	t_token		*prev;

	i = 0;
	curr = tokens;
	prev = NULL;
	while (curr && curr->type != TOK_PIPE)
	{
		if (is_valid_arg(curr, prev))
		{
			cmd_node->args[i++] = ft_strdup(curr->content);
		}
		if (curr->type == TOK_REDIR_IN || curr->type == TOK_REDIR_OUT
			|| curr->type == TOK_APPEND || curr->type == TOK_HEREDOC)
			curr = curr->next;
		prev = curr;
		curr = curr->next;
	}
	cmd_node->args[i] = NULL;
}

/**
 * @brief Extracts command arguments from token list into cmd_node->args.
 */
int	parse_args(t_node *cmd_node, t_token *tokens)
{
	int	count;

	count = count_args(tokens);
	cmd_node->args = malloc(sizeof(char *) * (count + 1));
	if (!cmd_node->args)
		return (1);
	fill_args(cmd_node, tokens);
	return (0);
}

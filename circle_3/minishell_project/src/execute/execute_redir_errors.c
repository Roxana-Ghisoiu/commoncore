/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir_errors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:02:39 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/15 15:21:16 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if a redirection token is followed by a valid word.
 * 
 * Ensures that redirection tokens like <, >, >>, << are followed by
 * a TOK_WORD (optionally after a TOK_SPACE if ai).
 * 
 * @param tokens Pointer to the first token in the list.
 * @return int 1 if error found, 0 if valid.
 */
int	check_redirection_syntax(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == TOK_REDIR_IN
			|| current->type == TOK_REDIR_OUT
			|| current->type == TOK_APPEND
			|| current->type == TOK_HEREDOC)
		{
			if (!current->next || current->next->type != TOK_WORD)
			{
				ft_putstr_fd
				("minishell: syntax error near unexpected token `", 2);
				if (current->next)
					ft_putstr_fd(current->next->content, 2);
				else
					ft_putstr_fd("newline", 2);
				ft_putendl_fd("'", 2);
				return (1);
			}
		}
		current = current->next;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:32:52 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/16 16:39:31 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Detects redirection or pipe tokens and adds them to the token list.
 *
 * Handles <<, >>, <, > and | by reading characters from the input and creating
 * appropriate token strings, which are passed to create_and_add_token().
 *
 * @param tokens Pointer to the token list.
 * @param input The input string.
 * @param i Pointer to the current position in the string.
 */
void	handle_special_token(t_token **tokens, const char *input, int *i)
{
	char	*str;

	if (input[*i] == '>' && input[*i + 1] == '>')
	{
		str = ft_strdup(">>");
		(*i) += 2;
	}
	else if (input[*i] == '<' && input[*i + 1] == '<')
	{
		str = ft_strdup("<<");
		(*i) += 2;
	}
	else
	{
		str = ft_substr(input, *i, 1);
		(*i)++;
	}
	create_and_add_token(tokens, str, false);
}

/**
 * @brief Assigns a token type (e.g., REDIR_IN, APPEND, PIPE) based on content.
 *
 * Matches the token string content and sets its type accordingly. 
 * If no special symbol is found, defaults to TOK_WORD.
 *
 * @param token The token to set the type for.
 */

void	set_token_type(t_token *token)
{
	if (ft_strncmp(token->content, "<<", 3) == 0)
		token->type = TOK_HEREDOC;
	else if (ft_strncmp(token->content, "<", 2) == 0)
		token->type = TOK_REDIR_IN;
	else if (ft_strncmp(token->content, ">>", 3) == 0)
		token->type = TOK_APPEND;
	else if (ft_strncmp(token->content, ">", 2) == 0)
		token->type = TOK_REDIR_OUT;
	else if (ft_strncmp(token->content, "|", 2) == 0)
		token->type = TOK_PIPE;
	else
		token->type = TOK_WORD;
}

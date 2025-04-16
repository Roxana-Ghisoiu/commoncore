/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:34:37 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/15 19:36:04 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Converts token type to string.
 */
static const char	*get_token_type_str(t_token_type type)
{
	if (type == TOK_WORD)
		return ("WORD");
	else if (type == TOK_PIPE)
		return ("PIPE");
	else if (type == TOK_REDIR_IN)
		return ("REDIR_IN");
	else if (type == TOK_REDIR_OUT)
		return ("REDIR_OUT");
	else if (type == TOK_APPEND)
		return ("APPEND");
	else if (type == TOK_HEREDOC)
		return ("HEREDOC");
	else
		return ("UNKNOWN");
}

/**
 * @brief Writes a string followed by a newline to STDOUT.
 */
static void	write_line(const char *str)
{
	write(STDOUT_FILENO, str, ft_strlen(str));
	write(STDOUT_FILENO, "\n", 1);
}

/**
 * @brief Converts an integer to string (simplified version).
 */
static void	write_index(int i)
{
	char	*prefix;
	char	*index_str;

	prefix = "[";
	write(STDOUT_FILENO, prefix, 1);
	index_str = ft_itoa(i);
	write(STDOUT_FILENO, index_str, ft_strlen(index_str));
	free(index_str);
	write(STDOUT_FILENO, "] ", 2);
}

/**
 * @brief Prints all tokens (type, content, quoted) using write().
 */
void	debug_print_tokens(t_token *tokens)
{
	int			i;
	const char	*type;

	write_line("\n--- TOKEN LIST ---");
	i = 0;
	while (tokens)
	{
		write_index(i);
		write(STDOUT_FILENO, "Type: ", 6);
		type = get_token_type_str(tokens->type);
		write(STDOUT_FILENO, type, ft_strlen(type));
		write(STDOUT_FILENO, " | Content: \"", 13);
		write(STDOUT_FILENO, tokens->content, ft_strlen(tokens->content));
		write(STDOUT_FILENO, "\" | Quoted: ", 12);
		if (tokens->was_quoted)
			write(STDOUT_FILENO, "true", 4);
		else
			write(STDOUT_FILENO, "false", 5);
		write(STDOUT_FILENO, "\n", 1);
		tokens = tokens->next;
		i++;
	}
	write_line("--- END OF TOKENS ---\n");
}

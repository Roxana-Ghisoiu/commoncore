/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:17:05 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/10 16:44:42 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Creates a new token and adds it to the list.
 *
 * @param tokens Pointer to the token list.
 * @param content The string content of the token.
 * @param quoted Indicates whether the token was quoted.
 */
static void	create_and_add_token(t_token **tokens, char *content, bool quoted)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->content = content;
	new->was_quoted = quoted;
	new->type = TOK_WORD;
	new->next = NULL;
	new->prev = NULL;
	add_token_back(tokens, new);
}

/**
 * @brief Extracts a quoted token from the input and adds it to the list.
 *
 * @param tokens Pointer to the head of the token list.
 * @param input The full input string.
 * @param i Pointer to the current index in the input.
 */
static void	handle_quoted_token(t_token **tokens, const char *input, int *i)
{
	int		start;
	char	quote;
	char	*content;

	quote = input[*i];
	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] == quote)
	{
		content = ft_substr(input, start, *i - start);
		if (content)
			create_and_add_token(tokens, content, true);
		(*i)++;
	}
}

/**
 * @brief Extracts an unquoted token from the input and adds it to the list.
 *
 * @param tokens Pointer to the head of the token list.
 * @param input The full input string.
 * @param i Pointer to the current index in the input.
 */
static void	handle_unquoted_token(t_token **tokens, const char *input, int *i)
{
	int		start;
	char	*content;

	start = *i;
	while (input[*i] && input[*i] != ' ')
		(*i)++;
	content = ft_substr(input, start, *i - start);
	create_and_add_token(tokens, content, false);
}

/**
 * @brief Splits the input line into a list of tokens, preserving quote info.
 *
 * This function builds a linked list of tokens from the user input,
 * marking each token as quoted or not, which is essential for handling
 * globbing and variable expansion correctly.
 *
 * @param input The input string.
 * @return t_token* A linked list of tokens.
 */
t_token	*tokenize_input(const char *input)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (input[i] == '\"' || input[i] == '\'')
			handle_quoted_token(&tokens, input, &i);
		else if (input[i])
			handle_unquoted_token(&tokens, input, &i);
	}
	return (tokens);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokens_asterisk.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghisoiu <rghisoiu@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:22:00 by rghisoiu          #+#    #+#             */
/*   Updated: 2025/04/10 11:57:52 by rghisoiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Adds a token to the end of a doubly linked list.
 * 
 * @param lst Pointer to the list head.
 * @param new Token to be added.
 */
void	add_token_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
}

/**
 * @brief Calculates the number of tokens in a linked list.
 * 
 * @param tokens Pointer to the head of the token list.
 * @return int Number of tokens.
 */
int	tokens_len(t_token *tokens)
{
	int	len;

	len = 0;
	while (tokens)
	{
		len++;
		tokens = tokens->next;
	}
	return (len);
}

/**
 * @brief Converts a token list into a string array
 *  (char **) with globbing support.
 * 
 * If the token content includes an unquoted asterisk (*),
 * it is replaced by matching filenames.
 * Otherwise, the token content is duplicated as-is.
 * 
 * @param tokens Pointer to the head of the token list.
 * @return char** Array of strings representing command arguments.
 */
char	**extract_args_from_tokens(t_token *tokens)
{
	char	**args;
	int		i;
	int		len;

	len = tokens_len(tokens);
	args = malloc(sizeof(char *) * (len + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (tokens)
	{
		if (has_unquoted_asterisk(tokens->content) && !tokens->was_quoted)
			args[i] = replace_asterisk_with_files(tokens->content);
		else
			args[i] = ft_strdup(tokens->content);
		i++;
		tokens = tokens->next;
	}
	args[i] = NULL;
	return (args);
}
